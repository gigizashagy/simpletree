#ifndef SIMPLETREE_H
#define SIMPLETREE_H

#include <vector>
#include <iostream>


template < typename T>
class TreeNode
{
public:
    TreeNode()
        : data(nullptr), parent(nullptr)
    {}

    TreeNode(const T& data, TreeNode* parent = nullptr)
        : data(data), parent(parent)
    {
        //TODO move/ copy data
    }
    TreeNode(const TreeNode& other)
    {
        this = other;
    }
    TreeNode(TreeNode&& other) noexcept
    {
        this = std::move(other);
    }
    ~TreeNode()
    {
        parent = nullptr;
        for (auto *node : children)
            delete node;
    }
    TreeNode& operator=(const TreeNode& other) = delete;
    TreeNode& operator=(TreeNode&& other) noexcept
    {
        if (this == &other)
            return *this;
        data = std::exchange(other.data, nullptr);
        parent = std::exchange(other.parent, nullptr);
        children = std::move(other.children);
        for (size_t i = 0 ; i < children ; ++i)
            children[i].parent = this;
        return *this;
    }

    bool operator==(const T& other)
    {
        return data == other;
    }
    bool operator==(const TreeNode& other)
    {
        return data == other.data;
    }
    bool operator!=(const T& other)
    {
        return data != other;
    }
    bool operator!=(const TreeNode& other)
    {
        return !(this == other);
    }

    void addChild (const T& data)
    {
        children.push_back(new TreeNode(data, this));
    }

    int getNumChildren()
    {
        return children.size();
    }

    void removeChild( const T& t )
    {
        for ( size_t i = 0 ; i < children.size() ; ++i )
        {
            if ( children.at(i).t == t )
            {
                children.erase( children.begin()+i );
                return;
            }
        }
    }
    void removeChildByIndex( const int index )
    {
        children.erase( children.begin()+index );
    }
    void setValue( const T& data )
    {
        this->data = data;
    }

    T& value()
    {
        return data;
    }
    const T& value() const
    {
        return data;
    }

    TreeNode* getParent() const
    {
        return parent;
    }

    std::vector< TreeNode* >& getChildren()
    {
        return children;
    }

    const std::vector< TreeNode* >& getChildren() const
    {
        return children;
    }

    void print( const int depth = 0 ) const
        {
            for ( int i = 0 ; i < depth ; ++i )
            {
                if ( i != depth-1 )
                    std::cout << "    ";
                else
                    std::cout << "|-- ";
            }
            std::cout << this->data << std::endl;
            for ( size_t i = 0 ; i < children.size() ; ++i )
            {
                children.at(i)->print( depth+1 );
            }
        }

private:
    T data;
    TreeNode *parent;
    std::vector<TreeNode*> children;
};




#endif // SIMPLETREE_H
