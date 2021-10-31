#pragma once

#include <memory>
#include <iostream>

namespace bintree {
    template <typename T>
    struct TNode: public std::enable_shared_from_this<TNode<T>> {
        using TNodePtr = std::shared_ptr<TNode<T>>;
        using TNodeParentPtr = std::weak_ptr<TNode<T>>;
        using TNodeConstPtr = std::shared_ptr<const TNode<T>>;

        bool hasLeft() const {
            return bool(left);
        }

        bool hasRight() const {
            return bool(right);
        }

        bool hasParent() const {
            return bool(parent);
        }

        T& getValue() {
            return value;
        }

        const T& getValue() const {
            return value;
        }

        TNodePtr getLeft() {
            return left;
        }

        TNodeConstPtr getLeft() const {
            return left;
        }

        TNodePtr getRight() {
            return right;
        }

        TNodeConstPtr getRight() const {
            return right;
        }

        TNodePtr getParent() {
            return parent.lock();
        }

        TNodeConstPtr getParent() const {
            return parent.lock();
        }

        static TNodePtr createLeaf(T v) {
            return std::make_shared<_make_shared_enabler<T>>(v);
        }

        bool operator ==(TNode<T> const& b) {
            return this->value == b.value;
        }

        TNodePtr getShared() {
            // Need to get right smart pointer then use object
            return std::enable_shared_from_this<TNode<T>>::shared_from_this();
        }

        static TNodePtr fork(T v, TNode* left, TNode* right) {
            TNodePtr ptr = std::make_shared<_make_shared_enabler<T, TNodePtr, TNodePtr>>(v, left->getShared(), right->getShared());
            // FIX: child shouldn`t have ownership on object. Clear pass
            TNodeParentPtr p = ptr;
            setParent(ptr->getLeft(), p);
            setParent(ptr->getRight(), p);
            return ptr;
        }

        TNodePtr replaceLeft(TNodePtr l) {
            // When set parent you create at least a second shared_ptr to that parent Node object.
            // So, when it is destroyed, memory will be freed at least twice
            setParent(l, std::enable_shared_from_this<TNode<T>>::weak_from_this());
            setParent(left, TNodeParentPtr());
            std::swap(l, left);
            return l;
        }

        TNodePtr replaceRight(TNodePtr r) {
            // When set parent you create at least a second shared_ptr to that parent Node object.
            // So, when it is destroyed, memory will be freed at least twice
            setParent(r, std::enable_shared_from_this<TNode<T>>::weak_from_this());
            setParent(right, TNodeParentPtr());
            std::swap(r, right);
            return r;
        }

        TNodePtr replaceRightWithLeaf(T v) {
            return replaceRight(createLeaf(v));
        }

        TNodePtr replaceLeftWithLeaf(T v) {
            return replaceLeft(createLeaf(v));
        }

        TNodePtr removeLeft() {
            return replaceLeft(nullptr);
        }
        TNodePtr removeRight() {
            return replaceRight(nullptr);
        }

        /*
        // FIX: make_shared can`t use private constructor inside
        struct _make_shared_enabler: public TNode<T> {
            _make_shared_enabler(T v): TNode<T>(v) {};
        };
        */


        template<typename... Args>
        struct _make_shared_enabler: public TNode<T> {
            _make_shared_enabler(Args...args): TNode<T>(args...) {};
        };


    private:
        T value;
        TNodePtr left = nullptr;
        TNodePtr right = nullptr;
        TNodeParentPtr parent = TNodeParentPtr();

        TNode(T v)
                : value(v)
        {
        }
        TNode(T v, TNode* left, TNode* right)
                : value(v)
                , left(left)
                , right(right)
        {
        }

        TNode(T v, TNodePtr left, TNodePtr right)
                : value(v)
                , left(left)
                , right(right)
        {
        }

        static void setParent(TNodePtr node, TNodeParentPtr parent) {
            if (node)
                node->parent = parent;
        }
    };
}