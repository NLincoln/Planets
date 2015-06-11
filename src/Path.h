//
//
//
//
//

#pragma once

#include <map>
#include <queue>
#include <list>
#include <climits>

#define SP_INF LONG_MAX

typedef unsigned int uint;
template <typename Vertex, typename Edges = std::multimap<Vertex, Vertex>, typename Pred = std::less<Vertex> >
class ShortestPath
{
	struct SP_NODE
	{
		long cost;
		Vertex prev;
		Vertex Node;
	};

	typedef std::map<Vertex, SP_NODE*, Pred> NODE_MAP;
	NODE_MAP m_Nodes;
	
	void BuildShortestPath(Vertex Node, std::list<Vertex>& ShortestPath) {
		SP_NODE* SPNode = GetSPNode(Node);
		if(SPNode->prev != NULL)
			BuildShortestPath(SPNode->prev, ShortestPath);
		ShortestPath.push_back(SPNode->Node);
	}

	SP_NODE* GetSPNode(Vertex value) {
		SP_NODE* node;
		typename NODE_MAP::iterator it;
		it = m_Nodes.find(value);

		if(it == m_Nodes.end())
		{
			node = new SP_NODE;
			node->Node = value;
			node->cost = SP_INF;
			node->prev = NULL;
			m_Nodes[value] = node;
		}
		else
			node = (*it).second;
		return node;
	}
	

	
public:
	ShortestPath(){};
	virtual ~ShortestPath(){};

	uint Resolve(Edges& edges, Vertex pFrom, Vertex pTo, std::list<Vertex>& ShortestPath) {

		std::queue<SP_NODE*> q;
		SP_NODE* SPNode;

		m_Nodes.clear();

		SPNode = GetSPNode(pFrom);
		SPNode->cost = 0;
		SPNode->prev = NULL;

		q.push(SPNode);

		while(q.size() > 0)
		{
			SPNode = q.front();
			q.pop();
			Vertex pINode = SPNode->Node;
			typename Edges::iterator it;
			typename Edges::iterator upper = edges.upper_bound(pINode);
			for(it = edges.lower_bound(pINode); it != upper; it++)
			{
				Vertex pAdjacent = (*it).second;
				SP_NODE* PRAdjacent = GetSPNode(pAdjacent);
				if((PRAdjacent->cost == SP_INF) || (PRAdjacent->cost > (SPNode->cost + 1)))
				{
					PRAdjacent->cost = SPNode->cost + 1;
					PRAdjacent->prev = SPNode->Node;
					q.push(PRAdjacent);
				}
			}
		}
		BuildShortestPath(pTo, ShortestPath);

		for(typename NODE_MAP::iterator it = m_Nodes.begin(); it != m_Nodes.end(); it++)
		{
			SP_NODE* SP_del = (*it).second;
			delete SP_del;
		}

		m_Nodes.clear();

		Vertex front = ShortestPath.front();
		Vertex back  = ShortestPath.back();

		if((front == pFrom) && (back == pTo))
			return ShortestPath.size();
		else return 0;
		
	}
};
