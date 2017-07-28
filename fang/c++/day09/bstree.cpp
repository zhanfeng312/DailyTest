#include <iostream>
#include <vector>
#include <stack>
using namespace std;
//有序二叉树(二叉搜索树)
class Tree{
    public:
        //构造过程中初始化为空树
        Tree(void) : m_root(NULL), m_size(0){}
        //析构过程中销毁剩余的节点
        ~Tree(void){
            clear();
        }
        //插入数据
        void insert(int data){
            //插入到以m_root为根的子树中
            insert(new Node(data), m_root);
            m_size++;
        }
        //删除第一个匹配数据,不存在返回false
        bool erase(int data){
            Node*& node = find(data, m_root);
            if (node){ 
                //左插右
                insert(node->m_left, node->m_right);
                Node* temp = node;
                //右提升
                node = node->m_right;
                delete temp;
                --m_size;
                return true;
            }
            return false;
        }
        //删除所有匹配的数据
        void remove(int data){
            while(erase(data));
        }
        //清空树
        void clear(void){
            clear(m_root);
            m_size = 0;
        }
        //将所有的_old替换为_new
        void updata(int _old, int _new){
            //删一个,插一个
            while(erase(_old))
                insert(_new);
        }
        //判断data是否存在
        bool find(int data){
            return find(data, m_root) != NULL;
        }
        //中序遍历
        void travel(void){
            travel(m_root);
            cout << endl;
        }
        //获取大小
        size_t size(void){
            return m_size;
        }
        //获取树高
        size_t height(void){
            return height(m_root);
        }
    private:
        //节点
        class Node{
        public:
            Node(int data) : m_data(data),
            m_left(NULL), m_right(NULL){}
            int m_data; //数据
            Node* m_left; //左树
            Node* m_right; //右树
        };
        //将node节点插入到以tree节点为根节点的子树中
        void insert (Node* node, Node*& tree){
            //如果为空树
            if(! tree)
                tree = node;
            else if(node){ 
                if(node->m_data < tree->m_data)
                    insert(node, tree->m_left);
                else
                    insert(node, tree->m_right);
            }
        }
        void clear(Node*& tree){
            if(tree){
                clear(tree->m_left);
                clear(tree->m_right);
                delete tree;
                tree = NULL;
            }
        }
        //返回子树tree中值与data相匹配的节点的父节点中指向
        //该节点的成员变量的别名
        Node*& find(int data, Node*& tree){
            if(! tree)
                return tree;
            else if(data == tree->m_data)
                return tree;
            else
                if(data < tree->m_data)
                    return find(data, tree->m_left);
                else
                    return find(data, tree->m_right);
        }
        //非递归实现
        void travel(Node* tree){
            stack<Node*, vector<Node*> > ss;
            if (! tree)
                return;
            Node* p = tree;
            while (p || !ss.empty()){
                if (p){
                    ss.push(p);//根指针进栈，遍历左子树
                    p = p->m_left;
                }
                else{
                    //根指针退栈，访问根节点，遍历右子树
                    cout << (ss.top())->m_data << ' ';
                    p = ss.top();
                    ss.pop();
                    p = p->m_right;
                }
            }
        }
        size_t height(Node* tree){
            if(tree){
                size_t lh = height(tree->m_left);
                size_t rh = height(tree->m_right);
                return (lh > rh ? lh : rh ) + 1;
            }
            return 0;
        }
        Node* m_root; //树根
        size_t m_size; //大小
};
int main(void){
    Tree tree;
    tree.insert(50);
    tree.insert(70);
    tree.insert(20);
    tree.insert(60);
    tree.insert(40);
    tree.insert(30);
    tree.insert(10);
    tree.insert(90);
    tree.insert(80);
    tree.travel();
    cout << tree.size() << ' ' << tree.height() << endl;
    tree.erase(70);
    tree.travel();
    tree.insert(70);
    tree.insert(70);
    tree.insert(70);
    tree.travel();
    tree.remove(70);
    tree.travel();
    tree.insert(40);
    tree.insert(40);
    tree.travel();
    tree.updata(40, 69);
    tree.travel();
    cout << boolalpha << tree.find(50) << endl;
    cout << boolalpha << tree.find(89) << endl;
    tree.clear();
    tree.travel();
    return 0;
}
