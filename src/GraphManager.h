//
//
//
//
//
#pragma once

#include <vector>
#include <list>

typedef unsigned int uint;

template<typename T>
class GraphData;

template <typename T>
struct Graph_Edge
{
	GraphData<T>* pDestination;
	double Cost;
};

struct Point
{
	uint x;
	uint y;
};

template<typename T>
bool DepthFirst_iter(GraphData<T>* Start, GraphData<T>* End, std::vector<GraphData<T>*>* Searched)
{
	if (Start == NULL)
		return false;
	if (Start == End)
		return true;
	Searched->push_back(Start);
	std::vector<Graph_Edge<T>> Neighbors = Start->GetAllNeighbors();
	for (uint i = 0; i < Neighbors.size(); ++i)
	{
		//Make sure that the node hasn't already been searched.
		if (std::find(Searched->begin(), Searched->end(), Neighbors[i].pDestination) == Searched->end())
			if (DepthFirst_iter(Neighbors[i].pDestination, End, Searched) == true)
				return true;
	}
	return false;
}

template<typename T>
bool DepthFirst(GraphData<T>* Start, GraphData<T>* End)
{
	std::vector<GraphData<T>*>* Searched = new std::vector < GraphData<T>* >;
	if (Start == End)
		return true;
	Searched->push_back(Start);
	std::vector<Graph_Edge<T>> Neighbors = Start->GetAllNeighbors();
	for (uint i = 0; i < Neighbors.size(); ++i)
	{
		if (DepthFirst_iter(Neighbors[i].pDestination, End, Searched) == true)
			return true;
	}
	return false;
}


template <typename T>
class GraphData
{
	T* m_pData;
	Point m_Position;
	std::vector<Graph_Edge<T>> m_Neighbors;

public:
	void AddNeighbor(GraphData<T>* _new, double _cost)
	{
		for (uint i = 0; i < m_Neighbors.size(); ++i)
		{
			if (_new == m_Neighbors[i].pDestination)
				return;
		}
		Graph_Edge<T> t;
		t.Cost = _cost;
		t.pDestination = _new;
		m_Neighbors.push_back(t);
	}

	void AddNeighbor(GraphData<T>* _new)
	{
		for (uint i = 0; i < m_Neighbors.size(); ++i)
		{
			if (_new == m_Neighbors[i].pDestination)
				return;
		}
		double cost = std::sqrt(DistanceSquared(m_Position, _new->m_Position));
		Graph_Edge<T> t = {/*Destination, then cost*/ _new, cost };
		m_Neighbors.push_back(t);
	}

	Graph_Edge<T> GetNeighborEdge(uint _Index)
	{
		return m_Neighbors[_index];
	}

	std::vector<Graph_Edge<T>> GetAllNeighbors()
	{
		return m_Neighbors;
	}

	double GetNeighborTravelCost(uint _Index)
	{
		return m_Neighbors[_index].Cost;
	}

	GraphData<T>* GetNeighborPlanet(uint _Index)
	{
		return m_Neighbors[_index].pDestination;
	}

	void SetPosition(Point _point)
	{
		m_Position = _point;
	}

	uint GetNumNeighbors()
	{
		return (uint) m_Neighbors.size();
	}

	Point GetPosition()
	{
		return m_Position;
	}

	T* GetDataRef()
	{
		return m_pData;
	}

	explicit GraphData(T* _ptr)
	{
		m_pData = _ptr;
	}

	~GraphData() {}
};

struct GRAPH_DESC
{
	uint width;
	uint height;
	uint MinNumNeighbors;
	uint NumNodes;
	//Always leave room for more :)
};

template <typename T>
class GraphManager
{	
	std::vector<GraphData<T>*> m_GraphData;
	uint FIELD_WIDTH;
	uint FIELD_HEIGHT;
	uint MIN_NUM_NEIGHBORS;

	void Verify_Graph()
	{
		for (uint i = 0; i < m_GraphData.size(); ++i)
		{
			for (uint j = 0; j < m_GraphData.size(); ++j)
			{
				if (!DepthFirst(m_GraphData[i], m_GraphData[j]))
					__debugbreak();
			}
		}
	}

	void Combine_Subgraphs()
	{
		/*
		* Start out by attempting to divide the graph into subgraphs.
		* Then resolve those subgraphs
		*/
		std::vector<std::vector<GraphData<T>*>> Subgraphs;
		std::vector<GraphData<T>*> sub;
		std::vector<GraphData<T>*> NodesLeft = m_GraphData;
		while (NodesLeft.empty() == false)
		{
			GraphData<T>* t = NodesLeft[0];
			NodesLeft.erase(NodesLeft.begin());
			sub.push_back(t);
			for (uint i = 0; i < NodesLeft.size(); i++)
			{
				if (DepthFirst(t, NodesLeft[i]))
				{
					sub.push_back(NodesLeft[i]);
					NodesLeft.erase(NodesLeft.begin() + i);
				}
			}
			Subgraphs.push_back(sub);
			sub.clear();
		}
		GraphData<T>* First = Subgraphs[0][0];
		GraphData<T>* Second = Subgraphs[0][0];
		uint SFirst = 0;
		uint SSecond = 0;
		uint MinDistanceSquared = DistanceSquared(First->GetPosition(), Second->GetPosition());
		while (Subgraphs.size() > 1)
		{
			for (uint si = 0; si < Subgraphs.size(); ++si)
			{
				for (uint sj = 0; sj < Subgraphs.size(); ++sj)
				{
					for (uint gi = 0; gi < Subgraphs[si].size(); ++gi)
					{
						for (uint gj = 0; gj < Subgraphs[sj].size(); ++gj)
						{
							//Wow. This is... REALLY dumb. But it's literally the only way I can think of to do this. 
							if (si == sj) // We don't want to add connections within a subgraph
							{
								sj++;
								goto OutsideSubgraph;
							}
							GraphData<T>* tFirst = Subgraphs[si][gi];
							GraphData<T>* tSecond = Subgraphs[sj][gj];
							uint tDistance = DistanceSquared(tFirst->GetPosition(), tSecond->GetPosition());
							if (tDistance < MinDistanceSquared)
							{
								First = tFirst;
								Second = tSecond;
								MinDistanceSquared = tDistance;
								SFirst = si;
								SSecond = sj;
							}
						}
					}
				OutsideSubgraph:
					; // Needed because we technically do nothing here (yet?)
				}
			}
			/*
			* Take the two points that have the smallest distance between them
			* Form an edge between them
			*/
			First->AddNeighbor(Second);
			Second->AddNeighbor(First);

			/*The next step in the puzzle is to add the two subgraphs that they are in together. */
			Subgraphs[SFirst].insert(Subgraphs[SFirst].end(), Subgraphs[SSecond].begin(), Subgraphs[SSecond].end());
			Subgraphs.erase(Subgraphs.begin() + SSecond);
		}
	}
public:
	std::vector<GraphData<T>*>* operator-> ()
	{
		return &m_GraphData;
	}
	std::list<GraphData<T>*> FindPath(GraphData<T>* Start, GraphData<T>* End)
	{
		ShortestPath<GraphData<T>*> PathData;
		std::multimap<GraphData<T>*, GraphData<T>*> Edges;
		Path Path;
		uint length = PathData.Resolve(Edges, Start, End, Path);
		return Path;
	}

	uint GetNumNodes()
	{
		return (uint)m_GraphData.size();
	}
	void Create_Graph()
	{
		//Check that the GraphData list is initialized
		//I'm really just rewriting PlanetManager::Create_Universe() here
		std::vector<Point> Points;
		for (uint i = 0; i < m_GraphData.size(); ++i)
		{
		beginning:
			Point t;
			t.x = Rand::GetRandomUINT(0, FIELD_WIDTH);
			t.y = Rand::GetRandomUINT(0, FIELD_HEIGHT);
			//Make sure it's not a duplicate
			for (uint j = 0; j < Points.size(); ++j)
			{
				if (Points[j].x == t.x && Points[j].y == t.y)
					goto beginning;
			}
			Points.push_back(t);
			m_GraphData[i]->SetPosition(t);
		}
		for (uint i = 0; i < Points.size(); i++)
		{
			uint Radius = 5;
			while (m_GraphData[i]->GetNumNeighbors() < MIN_NUM_NEIGHBORS)
			{
				for (uint j = 0; j < Points.size(); ++j)
				{
					uint Distance = DistanceSquared(Points[i], Points[j]);
					if (Distance <= square(Radius) && Distance > 0) //The > 0 ensures that a planet won't be it's own neighbor
					{
						m_GraphData[i]->AddNeighbor(m_GraphData[j], std::sqrt(Distance));
						m_GraphData[j]->AddNeighbor(m_GraphData[i], std::sqrt(Distance));
					}
				}
				++Radius;
			}
		}
		Combine_Subgraphs();
	}

	void Add_Node(T* Node)
	{
		GraphData<T>* t = new GraphData<T>(Node);
		m_GraphData.push_back(t);
	}

	std::vector<GraphData<T>*> GetGraphData()
	{
		return m_GraphData;
	}
	GraphManager(GRAPH_DESC Desc)
	{
		FIELD_HEIGHT = Desc.height;
		FIELD_WIDTH = Desc.width;
		MIN_NUM_NEIGHBORS = Desc.MinNumNeighbors;
	}
	~GraphManager() 
	{
		// We are now responsible for destructing ourselves... Ironically, our initialization is only handled indirectly. That's kinda dangerous
		for (uint i = 0; i < m_GraphData.size(); ++i)
		{
			delete m_GraphData->at(i);
		}
	}
};
