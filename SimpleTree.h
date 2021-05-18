#ifndef SIMPLETREE_H
#define SIMPLETREE_H

#include <vector>
#include <iostream>


template < typename T>
class TreeNode
{
public:
    TreeNode(const T& data, TreeNode* parent = nullptr)
        : m_parent(parent)
    {
        std::cout << "Tree()" << std::endl;
        m_data = new T(data);
    }

    TreeNode(T&& data, TreeNode* parent = nullptr)
        : m_parent(parent)
    {
        std::cout << "Tree&&()" << std::endl;
        m_data =  new T(data);
    }

    TreeNode(TreeNode&& other) noexcept
    {
        std::cout << "Tree(&&other)" << std::endl;
        *this = std::move(other);
    }

    ~TreeNode()
    {
        std::cout << "~Tree" << std::endl;
        m_parent = nullptr;
        delete m_data;
        for (auto* node : m_children)
            delete node;
    }
    TreeNode& operator=(const TreeNode& other) = delete;
    TreeNode& operator=(TreeNode&& other) noexcept
    {
        std::cout << "Tree = &&other" << std::endl;
        if (this == other)
            return *this;
        if (m_data)
            delete  m_data;
        m_data = other.m_data;
        m_parent = other.m_data;
        m_children = std::move(other.m_children);

        for (auto* node : m_children)
            node->m_parent(this);

        other.m_data = nullptr;
        other.m_parent = nullptr;
        return *this;
    }

    bool operator==(const T& data)
    {
        return m_data == data;
    }
    bool operator==(const TreeNode& other)
    {
        return this == other.m_data;
    }
    bool operator!=(const T& data)
    {
        return !(this == data);
    }
    bool operator!=(const TreeNode& other)
    {
        return !(this == other);
    }

    void addChild (const T& data)
    {
        m_children.push_back(new TreeNode(data, this));
    }
    void addChild (T&& data)
    {
        m_children.push_back(new TreeNode(data, this));
    }
    void addChild (const TreeNode& node)
    {
        node.m_parent = this;
        m_children.push_back(node);
    }
    void addChild (TreeNode&& node)
    {
        node.m_parent = this;
        m_children.push_back(node);
    }

    int getNumChildren()
    {
        return m_children.size();
    }
/// remove first indexed child
    void removeChild( const T& t )
    {
        for ( size_t i = 0 ; i < m_children.size() ; ++i )
        {
            if ( m_children.at(i).t == t )
            {
                m_children.erase( m_children.begin()+i );

                return;
            }
        }
    }
    void removeChildByIndex( const int index )
    {
        m_children.erase(m_children.begin()+index);
       // if (it != m_children.end());

    }
    void setValue( const T& data )
    {
        this->data = data;
    }

    T& value()
    {
        return m_data;
    }
    const T& value() const
    {
        return m_data;
    }

    TreeNode* getParent() const
    {
        return m_parent;
    }

    std::vector< TreeNode* >& getChildren()
    {
        return m_children;
    }

    const std::vector< TreeNode* >& getChildren() const
    {
        return m_children;
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
            std::cout << this->m_data << std::endl;
            for ( size_t i = 0 ; i < m_children.size() ; ++i )
            {
                m_children.at(i)->print( depth+1 );
            }
        }

private:
    T* m_data;
    TreeNode *m_parent;
    std::vector<TreeNode*> m_children;
};




#endif // SIMPLETREE_H
