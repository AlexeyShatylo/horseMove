#pragma once

class Node
{
	Node* m_pNext;

public:
	Node() : m_pNext(NULL) {}
	Node(Node* pNode) : m_pNext(pNode){}
	virtual ~Node(){}

	void setNext(Node* pNext)
	{
		m_pNext = pNext;
	}

	Node* next()
	{
		return m_pNext;
	}

};

class List
{
	Node		m_head;
	unsigned	m_size;
public:
	List() : m_size(0) {}
	~List()	{}
	Node* insert(Node* pNode, Node* pNewNode)
	{
		if (pNewNode)
		{
			pNewNode->setNext(pNode->next());
			pNode->setNext(pNewNode);
			m_size++; 
		}

		return pNewNode;
	}

	Node* remove(Node* pNode)
	{
		Node* pCurrentNode = m_head.next();
		Node* pPrevNode = NULL;
		while (pCurrentNode)
		{
			if (pCurrentNode == pNode)
			{
				if (pPrevNode)
				{
					pPrevNode->setNext(pCurrentNode->next());
				}
				else
				{
					m_head.setNext(pCurrentNode->next());
				}
				pCurrentNode->setNext(NULL);
				if (m_size)
				{
					m_size--;
				}
				break;
			}
			pPrevNode = pCurrentNode;
			pCurrentNode = pCurrentNode->next();
		}

		return pCurrentNode;
	}

	int getSize()
	{
		return m_size;
	}

	Node* push(Node* pNode)
	{
		return insert(head(), pNode);
	}
	Node* pop()
	{
		Node* pNode = head();
		if (!pNode && !pNode->next())
		{
			return NULL;
		}
		return remove(pNode->next());
	}
	Node* next(Node* pNode)
	{
		if (pNode)
		{
			return pNode->next();
		}
		return NULL;
	}
	Node* head()
	{
		return &m_head;
	}
	void setHead(Node* pNode)
	{
		m_head.setNext(pNode);
	}

};

class PathElement : public Node
{
	int m_x;
	int m_y;
public:
	PathElement() : m_x(0), m_y(0){}
	PathElement(int x, int y) : m_x(x), m_y(y){}
	int getX() const { return m_x; }
	int getY() const { return m_y; }
	
	void setX(int x)
	{
		m_x = x;
	}

	void setY(int y)
	{
		m_y = y;
	}
	virtual ~PathElement(){}
};

/*class PathList : public List
{
public:
	PathList(){};
	PathElement* insert(PathElement* pPathElement, int x, int y)
	{
		PathElement* pNewPathElement = new PathElement(x, y);
		if (pNewPathElement)
		{
			return static_cast<PathElement*>(List::insert(pPathElement, pNewPathElement));
		}
		return pNewPathElement;
	}
	bool remove(PathElement* pPathElement)
	{
		if (remove(pPathElement))
		{
			delete pPathElement;
			return true;
		}
		return false;
	}
	PathElement* find(int x, int y)
	{
		PathElement* pPathElement = static_cast<PathElement*>(head());
		while (pPathElement)
		{
			pPathElement = static_cast<PathElement*>(pPathElement->next());
			if (pPathElement &&  pPathElement->getX() && pPathElement->getY())
			{
				break;
			}
		}
		return pPathElement;
	}
	PathElement* push(int x, int y)
	{
		PathElement* pNewPathElement = new PathElement(x, y);
		if (pNewPathElement)
		{
			return static_cast<PathElement*>(List::push(pNewPathElement));
		}
		return pNewPathElement;
	}

	bool pop()
	{
		PathElement* pPathElement = static_cast<PathElement*>(List::pop());
		if (pPathElement)
		{
			delete pPathElement;
			return true;
		}
		return false;
	}
};
*/
class ListNode : public Node
{
	List* m_plist;
public:
	ListNode() : m_plist(NULL) {}
	ListNode(List* pList) : m_plist(pList) {}
	~ListNode() {}

	List* get()
	{
		return m_plist;
	}

	void set(List* pList)
	{
		m_plist = pList;
	}
};
