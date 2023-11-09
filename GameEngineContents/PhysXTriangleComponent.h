#pragma once

#include <GameEngineCore/GameEngineComponent.h>
#include "PhysXDefault.h"
struct sTriangle
{
    UINT ID = -1;
	UINT NearID[3];
	float4 CenterPos = float4::ZERONULL;
	float Cost = -1;
	float Heuristic = -1;
	float Value = -1;

	struct compare
	{
		bool operator()(sTriangle a, sTriangle b);
	};
};


// 설명 :
class PhysXTriangleComponent : public GameEngineComponent, public PhysXDefault
{
	friend class compare;

public:
	// constrcuter destructer
	PhysXTriangleComponent();
	~PhysXTriangleComponent();

	// delete Function
	PhysXTriangleComponent(const PhysXTriangleComponent& _Other) = delete;
	PhysXTriangleComponent(PhysXTriangleComponent&& _Other) noexcept = delete;
	PhysXTriangleComponent& operator=(const PhysXTriangleComponent& _Other) = delete;
	PhysXTriangleComponent& operator=(PhysXTriangleComponent&& _Other) noexcept = delete;

	void CreatePhysXActors(const std::string& _MeshName,bool _InverseIndex = true, float _Ratio = 1.f, float4 _GeoMetryRot = { 0.0f, 0.0f });
	physx::PxTriangleMesh* GetTriMesh()
	{
		return TriMesh;
	}
	void SetNavigation()
	{
		UINT iTriangleSize = TriMesh->getNbTriangles();
		for (UINT i = 0; i < iTriangleSize; i++)
		{
			sTriangle Temp;
			Temp.ID = i;
			Temp.NearID;
			physx::PxTriangle TriangleTemp;
			physx::PxU32 VertexIndex[3];
			physx::PxMeshQuery::getTriangle(TriMesh, m_pRigidStatic->getGlobalPose(), i, TriangleTemp, VertexIndex, Temp.NearID);
			float4 Vertex0 = float4(TriangleTemp.verts[0].x, TriangleTemp.verts[0].y, TriangleTemp.verts[0].z);
			float4 Vertex1 = float4(TriangleTemp.verts[1].x, TriangleTemp.verts[1].y, TriangleTemp.verts[1].z);
			float4 Vertex2 = float4(TriangleTemp.verts[2].x, TriangleTemp.verts[2].y, TriangleTemp.verts[2].z);
			float4 Result = float4(
				((Vertex0.x + Vertex1.x + Vertex2.x) / 3.f),
				((Vertex0.y + Vertex1.y + Vertex2.y) / 3.f),
				((Vertex0.z + Vertex1.z + Vertex2.z) / 3.f));
			Temp.CenterPos = Result;
			vec_TriangleNav.push_back(Temp);
		}
		int a = 0;
	}
	bool FindRoad(float4 _Start, float4 _End);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void CustomFBXLoad(const std::string& _MeshName,float _Ratio, bool _InverseIndex);

private:
	// Phys액터 생성에 필요한 정보
	physx::PxCooking* m_pCooking = nullptr;
	bool m_bInit = false;

	std::vector<std::vector<physx::PxVec3>> VertexVec;
	std::vector<std::vector<physx::PxU32>> IndexVec;
	std::shared_ptr<class GameEngineFBXMesh> Mesh;
	physx::PxTriangleMesh* TriMesh = nullptr;

    std::vector<sTriangle> vec_TriangleNav;
	std::vector<sTriangle> vec_ResultRoad;

};
//
//#include <iostream>
//#include <vector>
//#include <queue>
//#include <cmath>
//#include <algorithm>
//
//using namespace std;
//
//// NavMesh의 Cell을 나타내는 구조체
//struct Cell {
//    int id; // Cell의 고유 번호
//    vector<int> vertices; // Cell의 버텍스들의 인덱스
//    vector<int> neighbors; // Cell의 이웃 Cell들의 인덱스
//    double cost; // Cell의 이동 비용
//    double heuristic; // Cell의 도착점까지의 예상 비용
//    double f; // Cell의 총 비용 (cost + heuristic)
//    int parent; // Cell의 부모 Cell의 인덱스
//};
//
//// NavMesh를 나타내는 클래스
//class NavMesh 
//{
//private:
//    vector<Cell> cells; // Cell들의 목록
//    vector<pair<double, double>> vertices; // 버텍스들의 좌표 목록
//    int start; // 시작점이 속한 Cell의 인덱스
//    int goal; // 도착점이 속한 Cell의 인덱스
//    vector<int> path; // 최단 경로를 저장할 벡터
//
//public:
//    // NavMesh의 생성자
//    NavMesh(vector<Cell> cells, vector<pair<double, double>> vertices, pair<double, double> start, pair<double, double> goal) {
//        this->cells = cells;
//        this->vertices = vertices;
//        this->start = findCell(start); // 시작점이 속한 Cell을 찾는다
//        this->goal = findCell(goal); // 도착점이 속한 Cell을 찾는다
//        this->path.clear(); // 경로를 비운다
//    }
//
//    // 주어진 좌표가 속한 Cell의 인덱스를 반환하는 함수
//    int findCell(pair<double, double> point) {
//        for (int i = 0; i < cells.size(); i++) { // 모든 Cell에 대해 반복한다
//            bool inside = true; // point가 Cell 안에 있는지 여부
//            for (int j = 0; j < cells[i].vertices.size(); j++) { // Cell의 모든 버텍스에 대해 반복한다
//                int k = (j + 1) % cells[i].vertices.size(); // 다음 버텍스의 인덱스
//                // point와 Cell의 엣지를 이루는 두 버텍스를 기준으로 외적을 구한다
//                double cross = (point.first - vertices[cells[i].vertices[j]].first) * (vertices[cells[i].vertices[k]].second - vertices[cells[i].vertices[j]].second)
//                    - (point.second - vertices[cells[i].vertices[j]].second) * (vertices[cells[i].vertices[k]].first - vertices[cells[i].vertices[j]].first);
//                if (cross < 0) { // 외적이 음수라면 point는 Cell의 외부에 있다
//                    inside = false;
//                    break;
//                }
//            }
//            if (inside) return i; // point가 Cell 안에 있다면 해당 Cell의 인덱스를 반환한다
//        }
//        return -1; // point가 어떤 Cell에도 속하지 않는다면 -1을 반환한다
//    }
//
//    // 두 Cell 사이의 거리를 반환하는 함수
//    double getDistance(int a, int b) {
//        // 두 Cell의 중심점의 좌표를 구한다
//        double ax = 0, ay = 0, bx = 0, by = 0;
//        for (int i = 0; i < cells[a].vertices.size(); i++) {
//            ax += vertices[cells[a].vertices[i]].first;
//            ay += vertices[cells[a].vertices[i]].second;
//        }
//        ax /= cells[a].vertices.size();
//        ay /= cells[a].vertices.size();
//        for (int i = 0; i < cells[b].vertices.size(); i++) {
//            bx += vertices[cells[b].vertices[i]].first;
//            by += vertices[cells[b].vertices[i]].second;
//        }
//        bx /= cells[b].vertices.size();
//        by /= cells[b].vertices.size();
//        // 두 중심점 사이의 유클리드 거리를 반환한다
//        return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
//    }
//
//    // A* 알고리즘을 이용하여 최단 경로를 찾는 함수
//    void findPath() 
//    {
//        // 우선순위 큐를 이용하여 비용이 낮은 Cell부터 방문한다
//        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
//        // 시작 Cell의 비용과 부모를 초기화한다
//        cells[start].cost = 0;
//        cells[start].heuristic = getDistance(start, goal);
//        cells[start].f = cells[start].cost + cells[start].heuristic;
//        cells[start].parent = -1;
//        // 시작 Cell을 우선순위 큐에 넣는다
//        pq.push({ cells[start].f, start });
//        // 우선순위 큐가 빌 때까지 반복한다
//        while (!pq.empty()) {
//            // 우선순위 큐에서 가장 비용이 낮은 Cell을 꺼낸다
//            int last = pq.top().second;
//            pq.pop();
//            // 도착 Cell에 도달했다면 반복을 종료한다
//            if (last == goal) break;
//            // 현재 Cell의 모든 이웃 Cell에 대해 반복한다
//            for (int near : cells[last].neighbors) {
//                // 이웃 Cell의 새로운 비용을 계산한다
//                double newCost = cells[last].cost + getDistance(last, next);
//                // 이웃 Cell의 비용이 새로운 비용보다 크거나 초기값이라면 갱신한다
//                if (cells[near].cost > newCost || cells[near].cost == -1) {
//                    cells[near].cost = newCost;
//                    cells[near].heuristic = getDistance(near, goal);
//                    cells[near].f = cells[near].cost + cells[near].heuristic;
//                    cells[near].parent = current;
//                    // 이웃 Cell을 우선순위 큐에 넣는다
//                    pq.push({ cells[next].f, next });
//                }
//            }
//        }
//        // 도착 Cell부터 역추적하여 경로를 구한다
//        int current = goal;
//        while (current != -1) {
//            path.push_back(current);
//            current = cells[current].parent;
//        }
//        // 경로를 뒤집는다
//        reverse(path.begin(), path.end());
//    }
//
//    // 최단 경로를 출력하는 함수
//    void printPath() {
//        cout << "The shortest path is:" << endl;
//        for (int i = 0; i < path.size(); i++) {
//            cout << "Cell " << cells[path[i]].id;
//            if (i < path.size() - 1) cout << " -> ";
//            else cout << endl;
//        }
//    }
//};
//
//// 메인 함수
//int main() {
//    // NavMesh의 Cell들을 생성한다
//    vector<Cell> cells;
//    cells.push_back({ 1, {0, 1, 2}, {1, 3}, -1, -1, -1, -1 }); // Cell 1
//    cells.push_back({ 2, {0, 2, 3}, {0, 2, 4}, -1, -1, -1, -1 }); // Cell 2
//    cells.push_back({ 3, {2, 3, 4}, {1, 3, 5}, -1, -1, -1, -1 }); // Cell 3
//    cells.push_back({ 4, {1, 2, 4, 5}, {0, 2, 4, 6}, -1, -1, -1, -1 }); // Cell 4
//    cells.push_back({ 5, {3, 4, 6}, {1, 3, 5, 7}, -1, -1, -1, -1 }); // Cell 5
//    cells.push_back({ 6, {4, 5, 7}, {2, 4, 6, 8}, -1, -1, -1, -1 }); // Cell 6
//    cells.push_back({ 7, {2, 4, 5, 8}, {3, 5, 7, 9}, -1, -1, -1, -1 }); // Cell 7
//    cells.push_back({ 8, {5, 6, 9}, {4, 6, 8, 10}, -1, -1, -1, -1 }); // Cell 8
//    cells.push_back({ 9, {4, 5, 6, 9}, {5, 7, 9, 11}, -1, -1, -1, -1 }); // Cell 9
//    cells.push_back({ 10, {6, 7, 10}, {6, 8, 10, 12}, -1, -1, -1, -1 }); // Cell 10
//    cells.push_back({ 11, {5, 6, 7, 10}, {7, 9, 11, 13}, -1, -1, -1, -1 }); // Cell 11
//    cells.push_back({ 12, {7, 8, 11}, {8, 10, 12, 14}, -1, -1, -1, -1 }); // Cell 12
//    cells.push_back({ 13, {6, 7, 8, 11}, {9, 11, 13, 15}, -1, -1, -1, -1 }); // Cell 13
//    cells.push_back({ 14, {8, 9, 12}, {10, 12, 14, 16}, -1, -1, -1, -1 }); // Cell 14
//    cells.push_back({ 15, {7, 8, 9, 12}, {11, 13, 15, 17}, -1, -1, -1, -1 }); // Cell 15
//    cells.push_back({ 16, {9, 10, 13}, {12, 14, 16, 18}, -1, -1, -1, -1 }); // Cell 16
//    cells.push_back({ 17, {8, 9, 10, 13}, {13, 15, 17, 19}, -1, -1, -1, -1 }); // Cell 17
//    cells.push_back({ 18, {10, 11, 14}, {14, 16, 18}, -1, -1, -1, -1 }); // Cell 18
//    cells.push_back({ 19, {9, 10, 11, 14}, {15, 17, 19}, -1, -1, -1, -1 }); // Cell 19
//
//    // NavMesh의 버텍스들의 좌표를 생성한다
//    vector<pair<double, double>> vertices;
//    vertices.push_back({ 0, 0 }); // Vertex 0
//    vertices.push_back({ 0, 5 }); // Vertex 1
//    vertices.push_back({ 5, 0 }); // Vertex 2
//    vertices.push_back({ 5, 5 }); // Vertex 3
//    vertices.push_back({ 10, 0 }); // Vertex 4
//    vertices.push_back({ 10, 5 }); // Vertex 5
//    vertices.push_back({ 15, 0 }); // Vertex 6
//    vertices.push_back({ 15, 5 }); // Vertex 7
//    vertices.push_back({ 20, 0 }); // Vertex 8
//    vertices.push_back({ 20, 5 }); // Vertex 9
//    vertices.push_back({ 25, 0 }); // Vertex 10
//    vertices.push_back({ 25, 5 }); // Vertex 11
//
//    // 시작점과 도착점의 좌표를 생성한다
//    pair<double, double> start = { 2, 2 }; // 시작점
//    pair<double, double> goal = { 23, 3 }; // 도착점
//
//    // NavMesh 객체를 생성한다
//    NavMesh navmesh(cells, vertices, start, goal);
//
//    // 최단 경로를 찾는다
//    navmesh.findPath();
//
//    // 최단 경로를 출력한다
//    navmesh.printPath();
//
//    return 0;
//}
