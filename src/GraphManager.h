//
//
//
//
//
#pragma once

#include <vector>
#include <list>

#include "Util.h"

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

	template <typename T>
	friend class GraphManager;
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

	double GetNeighborTravelCost(GraphData<T>* Node)
	{
		for (uint i = 0; i < m_Neighbors.size(); ++i)
		{
			if (m_Neighbors[i].pDestination == Node)
			{
				return m_Neighbors[i].Cost;
			}
		}
	}

	double GetNeighborTravelCost(T* Node)
	{
		for (uint i = 0; i < m_Neighbors.size(); ++i)
		{
			if (m_Neighbors[i].pDestination->GetDataRef() == Node) // Validate that this function works as advertised
			{
				return m_Neighbors[i].Cost;
			}
		}
		return 0;
	}

	double GetNeighborTravelCost(GraphData<T*> Node)
	{
		return GetNeighborTravelCost(Node->GetDataRef());
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

	bool operator==(GraphData<T*> c)
	{
		if (c.m_pData != m_pData)
			return false;
		if (c.m_Neighbors != m_Neighbors)
			return false;
		if (c.m_Position != m_Position)
			return false;
		return true;
	}

	bool operator!=(GraphData<T*> c)
	{
		return (!operator==(c));
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

	GraphData<T>* DataTypeToGraphData(T* DataType)
	{
		for (uint i = 0; i < m_GraphData.size(); ++i)
		{
			if (m_GraphData[i]->m_pData == DataType)
				return GraphData[i];
		}
		return NULL;
	}

public:

	bool CreateFromString(std::string state)
	{
		if (m_GraphData.size() == 0) // Make sure we don't already have a generated universe
			return false;
		// The first step is to parse it into an array of strings
		std::vector<std::string> PlanetList = ParseStringIntoArray(state, ';');
		for (uint i = 0; i < PlanetList.size(); ++i)
		{
			auto PosAndNeighbors = ParseStringIntoArray(PlanetList[i], ':')[1]; // Because c++ is now python
			GraphData<T>* GraphNode;
			std::string PosString = ParseStringIntoArray(PosAndNeighbors, ',')[0];
			std::string NeighborsString = ParseStringIntoArray(PosAndNeighbors, ',')[1];
			
			GraphNode->m_Position.x = atoi(ParseStringIntoArray(PosString, ' ')[0]);
		
		}
	}

	std::vector<T*> ShortestPath_Dijkstra(T* Start, T* End)
	{
		std::vector<T*> Out;
		GraphData<T>* StartNode = DataTypeToGraphData(Start);
		GraphData<T>* EndNode = DataTypeToGraphData(End);

		if (!StartNode || !EndNode) // Invalid Datanode refs. return an empty path.
			return Out;

		std::vector<GraphData<T>*> UnvisitedNodes = m_GraphData;
		std::vector<GraphData<T>*> VisitedNodes;

		std::vector<std::pair<GraphData<T>*, double>> Costs;

		auto QueryVectorPair = [](std::vector<std::pair<GraphData<T>*, double>> Costs, GraphData<T>* elem) // C++ is now javascript.
		{
			for (uint i = 0; i < Costs.size(); ++i)
			{
				if (std::get<0>(Costs[i]) == elem)
				{
					return std::get<1>(Costs[i]);
				}
			}
			return 0.0;
		};

		auto SetVectorPairEntry = [](std::vector<std::pair<GraphData<T>*, double>> Costs, GraphData<T>* elem, double NewVal)
		{
			for (uint i = 0; i < Costs.size(); ++i)
			{
				if (std::get<0>(Costs[i]) == elem)
				{
					std::get<1>(Costs[i]) = NewVal;
					return true;
				}
			}
			return false;
		};


		
		for (uint i = 0; i < UnvisitedNodes.size(); ++i) // Initialize the costs map
			Costs.push_back(std::pair<GraphData<T>*, double>(UnvisitedNodes[i], UINT_MAX));

		uint CurrentIndex = GetElementPositionInVector(StartNode, UnvisitedNodes);
		
		Costs[UnvisitedNodes[CurrentIndex]] = 0; // Initialize first element to 0. 
		VisitedNodes.push_back(UnvisitedNodes[CurrentIndex]);
		UnvisitedNodes.erase(UnvisitedNodes.begin() + CurrentIndex); // CurrentIndex is invalid after this step and will need to be recomputed before next use.

		auto FindSmallestDistanceNode = [&]()
		{
			GraphData<T>* Out;
			for (uint i = 0; i < UnvisitedNodes.size(); ++i)
			{
				if (Costs[UnvisitedNodes[i]] > Costs[Out])
					Out = UnvisitedNodes[i];
			}
			return Out;
		};

		// Go through the unvisited vertexes, from shortest distance to longest distance. Recompute the distances at each one. Then mark it as visited. 
		while (UnvisitedNodes.size() > 1)
		{

		}

	}

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
			delete m_GraphData[i];
		}
	}
};
