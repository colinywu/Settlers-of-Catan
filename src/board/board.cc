#include "vertex.h"
#include "edge.h"
#include <vector>
#include <algorithm>
#include <random>
#include "board.h"
#include <string>
#include <map>
#include <stdexcept>
#include <sstream>
#include "resourceType.h"

using namespace std;

Board::Board(const unsigned int seed) : gooseLocation{nullptr}, seed{seed}
{

  // vertices instantiation
  for (int i = 0; i < 54; i++)
  {
    vertices.emplace_back(std::make_unique<Vertex>(i));
  }

  // edge instantiation (with connected vectors)
  edges.emplace_back(std::make_unique<Edge>(0, vertices[0].get(), vertices[1].get()));
  edges.emplace_back(std::make_unique<Edge>(1, vertices[0].get(), vertices[3].get()));
  edges.emplace_back(std::make_unique<Edge>(2, vertices[1].get(), vertices[4].get()));
  edges.emplace_back(std::make_unique<Edge>(3, vertices[2].get(), vertices[3].get()));
  edges.emplace_back(std::make_unique<Edge>(4, vertices[4].get(), vertices[5].get()));
  edges.emplace_back(std::make_unique<Edge>(5, vertices[2].get(), vertices[7].get()));
  edges.emplace_back(std::make_unique<Edge>(6, vertices[3].get(), vertices[8].get()));
  edges.emplace_back(std::make_unique<Edge>(7, vertices[4].get(), vertices[9].get()));
  edges.emplace_back(std::make_unique<Edge>(8, vertices[5].get(), vertices[10].get()));
  edges.emplace_back(std::make_unique<Edge>(9, vertices[6].get(), vertices[7].get()));
  edges.emplace_back(std::make_unique<Edge>(10, vertices[8].get(), vertices[9].get()));
  edges.emplace_back(std::make_unique<Edge>(11, vertices[10].get(), vertices[11].get()));
  edges.emplace_back(std::make_unique<Edge>(12, vertices[6].get(), vertices[12].get()));
  edges.emplace_back(std::make_unique<Edge>(13, vertices[7].get(), vertices[13].get()));
  edges.emplace_back(std::make_unique<Edge>(14, vertices[8].get(), vertices[14].get()));
  edges.emplace_back(std::make_unique<Edge>(15, vertices[9].get(), vertices[15].get()));
  edges.emplace_back(std::make_unique<Edge>(16, vertices[10].get(), vertices[16].get()));
  edges.emplace_back(std::make_unique<Edge>(17, vertices[11].get(), vertices[17].get()));
  edges.emplace_back(std::make_unique<Edge>(18, vertices[13].get(), vertices[14].get()));
  edges.emplace_back(std::make_unique<Edge>(19, vertices[15].get(), vertices[16].get()));
  edges.emplace_back(std::make_unique<Edge>(20, vertices[12].get(), vertices[18].get()));
  edges.emplace_back(std::make_unique<Edge>(21, vertices[13].get(), vertices[19].get()));
  edges.emplace_back(std::make_unique<Edge>(22, vertices[14].get(), vertices[20].get()));
  edges.emplace_back(std::make_unique<Edge>(23, vertices[15].get(), vertices[21].get()));
  edges.emplace_back(std::make_unique<Edge>(24, vertices[16].get(), vertices[22].get()));
  edges.emplace_back(std::make_unique<Edge>(25, vertices[17].get(), vertices[23].get()));
  edges.emplace_back(std::make_unique<Edge>(26, vertices[18].get(), vertices[19].get()));
  edges.emplace_back(std::make_unique<Edge>(27, vertices[20].get(), vertices[21].get()));
  edges.emplace_back(std::make_unique<Edge>(28, vertices[22].get(), vertices[23].get()));
  edges.emplace_back(std::make_unique<Edge>(29, vertices[18].get(), vertices[24].get()));
  edges.emplace_back(std::make_unique<Edge>(30, vertices[19].get(), vertices[25].get()));
  edges.emplace_back(std::make_unique<Edge>(31, vertices[20].get(), vertices[26].get()));
  edges.emplace_back(std::make_unique<Edge>(32, vertices[21].get(), vertices[27].get()));
  edges.emplace_back(std::make_unique<Edge>(33, vertices[22].get(), vertices[28].get()));
  edges.emplace_back(std::make_unique<Edge>(34, vertices[23].get(), vertices[29].get()));
  edges.emplace_back(std::make_unique<Edge>(35, vertices[25].get(), vertices[26].get()));
  edges.emplace_back(std::make_unique<Edge>(36, vertices[27].get(), vertices[28].get()));
  edges.emplace_back(std::make_unique<Edge>(37, vertices[24].get(), vertices[30].get()));
  edges.emplace_back(std::make_unique<Edge>(38, vertices[25].get(), vertices[31].get()));
  edges.emplace_back(std::make_unique<Edge>(39, vertices[26].get(), vertices[32].get()));
  edges.emplace_back(std::make_unique<Edge>(40, vertices[27].get(), vertices[33].get()));
  edges.emplace_back(std::make_unique<Edge>(41, vertices[28].get(), vertices[34].get()));
  edges.emplace_back(std::make_unique<Edge>(42, vertices[29].get(), vertices[35].get()));
  edges.emplace_back(std::make_unique<Edge>(43, vertices[30].get(), vertices[31].get()));
  edges.emplace_back(std::make_unique<Edge>(44, vertices[32].get(), vertices[33].get()));
  edges.emplace_back(std::make_unique<Edge>(45, vertices[34].get(), vertices[35].get()));
  edges.emplace_back(std::make_unique<Edge>(46, vertices[30].get(), vertices[36].get()));
  edges.emplace_back(std::make_unique<Edge>(47, vertices[31].get(), vertices[37].get()));
  edges.emplace_back(std::make_unique<Edge>(48, vertices[32].get(), vertices[38].get()));
  edges.emplace_back(std::make_unique<Edge>(49, vertices[33].get(), vertices[39].get()));
  edges.emplace_back(std::make_unique<Edge>(50, vertices[34].get(), vertices[40].get()));
  edges.emplace_back(std::make_unique<Edge>(51, vertices[35].get(), vertices[41].get()));
  edges.emplace_back(std::make_unique<Edge>(52, vertices[37].get(), vertices[38].get()));
  edges.emplace_back(std::make_unique<Edge>(53, vertices[39].get(), vertices[40].get()));
  edges.emplace_back(std::make_unique<Edge>(54, vertices[36].get(), vertices[42].get()));
  edges.emplace_back(std::make_unique<Edge>(55, vertices[37].get(), vertices[43].get()));
  edges.emplace_back(std::make_unique<Edge>(56, vertices[38].get(), vertices[44].get()));
  edges.emplace_back(std::make_unique<Edge>(57, vertices[39].get(), vertices[45].get()));
  edges.emplace_back(std::make_unique<Edge>(58, vertices[40].get(), vertices[46].get()));
  edges.emplace_back(std::make_unique<Edge>(59, vertices[41].get(), vertices[47].get()));
  edges.emplace_back(std::make_unique<Edge>(60, vertices[42].get(), vertices[43].get()));
  edges.emplace_back(std::make_unique<Edge>(61, vertices[44].get(), vertices[45].get()));
  edges.emplace_back(std::make_unique<Edge>(62, vertices[46].get(), vertices[47].get()));
  edges.emplace_back(std::make_unique<Edge>(63, vertices[43].get(), vertices[48].get()));
  edges.emplace_back(std::make_unique<Edge>(64, vertices[44].get(), vertices[49].get()));
  edges.emplace_back(std::make_unique<Edge>(65, vertices[45].get(), vertices[50].get()));
  edges.emplace_back(std::make_unique<Edge>(66, vertices[46].get(), vertices[51].get()));
  edges.emplace_back(std::make_unique<Edge>(67, vertices[48].get(), vertices[49].get()));
  edges.emplace_back(std::make_unique<Edge>(68, vertices[50].get(), vertices[51].get()));
  edges.emplace_back(std::make_unique<Edge>(69, vertices[49].get(), vertices[52].get()));
  edges.emplace_back(std::make_unique<Edge>(70, vertices[50].get(), vertices[53].get()));
  edges.emplace_back(std::make_unique<Edge>(71, vertices[52].get(), vertices[53].get()));

  // connecting vertices to edges
  vertices[0].get()->connectedEdges.emplace_back(edges[0].get());
  vertices[0].get()->connectedEdges.emplace_back(edges[1].get());
  vertices[1].get()->connectedEdges.emplace_back(edges[0].get());
  vertices[1].get()->connectedEdges.emplace_back(edges[2].get());
  vertices[2].get()->connectedEdges.emplace_back(edges[3].get());
  vertices[2].get()->connectedEdges.emplace_back(edges[5].get());
  vertices[3].get()->connectedEdges.emplace_back(edges[1].get());
  vertices[3].get()->connectedEdges.emplace_back(edges[3].get());
  vertices[3].get()->connectedEdges.emplace_back(edges[6].get());
  vertices[4].get()->connectedEdges.emplace_back(edges[2].get());
  vertices[4].get()->connectedEdges.emplace_back(edges[4].get());
  vertices[4].get()->connectedEdges.emplace_back(edges[7].get());
  vertices[5].get()->connectedEdges.emplace_back(edges[4].get());
  vertices[5].get()->connectedEdges.emplace_back(edges[8].get());
  vertices[6].get()->connectedEdges.emplace_back(edges[9].get());
  vertices[6].get()->connectedEdges.emplace_back(edges[12].get());
  vertices[7].get()->connectedEdges.emplace_back(edges[5].get());
  vertices[7].get()->connectedEdges.emplace_back(edges[9].get());
  vertices[7].get()->connectedEdges.emplace_back(edges[13].get());
  vertices[8].get()->connectedEdges.emplace_back(edges[6].get());
  vertices[8].get()->connectedEdges.emplace_back(edges[10].get());
  vertices[8].get()->connectedEdges.emplace_back(edges[14].get());
  vertices[9].get()->connectedEdges.emplace_back(edges[7].get());
  vertices[9].get()->connectedEdges.emplace_back(edges[10].get());
  vertices[9].get()->connectedEdges.emplace_back(edges[15].get());
  vertices[10].get()->connectedEdges.emplace_back(edges[8].get());
  vertices[10].get()->connectedEdges.emplace_back(edges[11].get());
  vertices[10].get()->connectedEdges.emplace_back(edges[16].get());
  vertices[11].get()->connectedEdges.emplace_back(edges[11].get());
  vertices[11].get()->connectedEdges.emplace_back(edges[17].get());
  vertices[12].get()->connectedEdges.emplace_back(edges[12].get());
  vertices[12].get()->connectedEdges.emplace_back(edges[20].get());
  vertices[13].get()->connectedEdges.emplace_back(edges[13].get());
  vertices[13].get()->connectedEdges.emplace_back(edges[18].get());
  vertices[13].get()->connectedEdges.emplace_back(edges[21].get());
  vertices[14].get()->connectedEdges.emplace_back(edges[14].get());
  vertices[14].get()->connectedEdges.emplace_back(edges[18].get());
  vertices[14].get()->connectedEdges.emplace_back(edges[22].get());
  vertices[15].get()->connectedEdges.emplace_back(edges[15].get());
  vertices[15].get()->connectedEdges.emplace_back(edges[19].get());
  vertices[15].get()->connectedEdges.emplace_back(edges[23].get());
  vertices[16].get()->connectedEdges.emplace_back(edges[16].get());
  vertices[16].get()->connectedEdges.emplace_back(edges[19].get());
  vertices[16].get()->connectedEdges.emplace_back(edges[24].get());
  vertices[17].get()->connectedEdges.emplace_back(edges[17].get());
  vertices[17].get()->connectedEdges.emplace_back(edges[25].get());
  vertices[18].get()->connectedEdges.emplace_back(edges[20].get());
  vertices[18].get()->connectedEdges.emplace_back(edges[26].get());
  vertices[18].get()->connectedEdges.emplace_back(edges[29].get());
  vertices[19].get()->connectedEdges.emplace_back(edges[21].get());
  vertices[19].get()->connectedEdges.emplace_back(edges[26].get());
  vertices[19].get()->connectedEdges.emplace_back(edges[30].get());
  vertices[20].get()->connectedEdges.emplace_back(edges[22].get());
  vertices[20].get()->connectedEdges.emplace_back(edges[27].get());
  vertices[20].get()->connectedEdges.emplace_back(edges[31].get());
  vertices[21].get()->connectedEdges.emplace_back(edges[23].get());
  vertices[21].get()->connectedEdges.emplace_back(edges[27].get());
  vertices[21].get()->connectedEdges.emplace_back(edges[32].get());
  vertices[22].get()->connectedEdges.emplace_back(edges[24].get());
  vertices[22].get()->connectedEdges.emplace_back(edges[28].get());
  vertices[22].get()->connectedEdges.emplace_back(edges[33].get());
  vertices[23].get()->connectedEdges.emplace_back(edges[25].get());
  vertices[23].get()->connectedEdges.emplace_back(edges[28].get());
  vertices[23].get()->connectedEdges.emplace_back(edges[34].get());
  vertices[24].get()->connectedEdges.emplace_back(edges[29].get());
  vertices[24].get()->connectedEdges.emplace_back(edges[37].get());
  vertices[25].get()->connectedEdges.emplace_back(edges[30].get());
  vertices[25].get()->connectedEdges.emplace_back(edges[38].get());
  vertices[26].get()->connectedEdges.emplace_back(edges[31].get());
  vertices[26].get()->connectedEdges.emplace_back(edges[35].get());
  vertices[26].get()->connectedEdges.emplace_back(edges[39].get());
  vertices[27].get()->connectedEdges.emplace_back(edges[32].get());
  vertices[27].get()->connectedEdges.emplace_back(edges[36].get());
  vertices[27].get()->connectedEdges.emplace_back(edges[40].get());
  vertices[28].get()->connectedEdges.emplace_back(edges[33].get());
  vertices[28].get()->connectedEdges.emplace_back(edges[36].get());
  vertices[28].get()->connectedEdges.emplace_back(edges[41].get());
  vertices[29].get()->connectedEdges.emplace_back(edges[34].get());
  vertices[29].get()->connectedEdges.emplace_back(edges[42].get());
  vertices[30].get()->connectedEdges.emplace_back(edges[37].get());
  vertices[30].get()->connectedEdges.emplace_back(edges[43].get());
  vertices[30].get()->connectedEdges.emplace_back(edges[46].get());
  vertices[31].get()->connectedEdges.emplace_back(edges[38].get());
  vertices[31].get()->connectedEdges.emplace_back(edges[43].get());
  vertices[31].get()->connectedEdges.emplace_back(edges[47].get());
  vertices[32].get()->connectedEdges.emplace_back(edges[39].get());
  vertices[32].get()->connectedEdges.emplace_back(edges[44].get());
  vertices[32].get()->connectedEdges.emplace_back(edges[48].get());
  vertices[33].get()->connectedEdges.emplace_back(edges[40].get());
  vertices[33].get()->connectedEdges.emplace_back(edges[44].get());
  vertices[33].get()->connectedEdges.emplace_back(edges[49].get());
  vertices[34].get()->connectedEdges.emplace_back(edges[41].get());
  vertices[34].get()->connectedEdges.emplace_back(edges[45].get());
  vertices[34].get()->connectedEdges.emplace_back(edges[50].get());
  vertices[35].get()->connectedEdges.emplace_back(edges[42].get());
  vertices[35].get()->connectedEdges.emplace_back(edges[45].get());
  vertices[35].get()->connectedEdges.emplace_back(edges[51].get());
  vertices[36].get()->connectedEdges.emplace_back(edges[46].get());
  vertices[36].get()->connectedEdges.emplace_back(edges[54].get());
  vertices[37].get()->connectedEdges.emplace_back(edges[47].get());
  vertices[37].get()->connectedEdges.emplace_back(edges[52].get());
  vertices[37].get()->connectedEdges.emplace_back(edges[55].get());
  vertices[38].get()->connectedEdges.emplace_back(edges[48].get());
  vertices[38].get()->connectedEdges.emplace_back(edges[52].get());
  vertices[38].get()->connectedEdges.emplace_back(edges[56].get());
  vertices[39].get()->connectedEdges.emplace_back(edges[49].get());
  vertices[39].get()->connectedEdges.emplace_back(edges[53].get());
  vertices[39].get()->connectedEdges.emplace_back(edges[57].get());
  vertices[40].get()->connectedEdges.emplace_back(edges[50].get());
  vertices[40].get()->connectedEdges.emplace_back(edges[53].get());
  vertices[40].get()->connectedEdges.emplace_back(edges[58].get());
  vertices[41].get()->connectedEdges.emplace_back(edges[51].get());
  vertices[41].get()->connectedEdges.emplace_back(edges[59].get());
  vertices[42].get()->connectedEdges.emplace_back(edges[54].get());
  vertices[42].get()->connectedEdges.emplace_back(edges[60].get());
  vertices[43].get()->connectedEdges.emplace_back(edges[55].get());
  vertices[43].get()->connectedEdges.emplace_back(edges[60].get());
  vertices[43].get()->connectedEdges.emplace_back(edges[63].get());
  vertices[44].get()->connectedEdges.emplace_back(edges[56].get());
  vertices[44].get()->connectedEdges.emplace_back(edges[61].get());
  vertices[44].get()->connectedEdges.emplace_back(edges[64].get());
  vertices[45].get()->connectedEdges.emplace_back(edges[57].get());
  vertices[45].get()->connectedEdges.emplace_back(edges[61].get());
  vertices[45].get()->connectedEdges.emplace_back(edges[64].get());
  vertices[45].get()->connectedEdges.emplace_back(edges[57].get());
  vertices[45].get()->connectedEdges.emplace_back(edges[61].get());
  vertices[45].get()->connectedEdges.emplace_back(edges[65].get());
  vertices[46].get()->connectedEdges.emplace_back(edges[58].get());
  vertices[46].get()->connectedEdges.emplace_back(edges[62].get());
  vertices[46].get()->connectedEdges.emplace_back(edges[66].get());
  vertices[47].get()->connectedEdges.emplace_back(edges[59].get());
  vertices[47].get()->connectedEdges.emplace_back(edges[62].get());
  vertices[48].get()->connectedEdges.emplace_back(edges[63].get());
  vertices[48].get()->connectedEdges.emplace_back(edges[67].get());
  vertices[49].get()->connectedEdges.emplace_back(edges[64].get());
  vertices[49].get()->connectedEdges.emplace_back(edges[67].get());
  vertices[49].get()->connectedEdges.emplace_back(edges[69].get());
  vertices[50].get()->connectedEdges.emplace_back(edges[65].get());
  vertices[50].get()->connectedEdges.emplace_back(edges[68].get());
  vertices[50].get()->connectedEdges.emplace_back(edges[70].get());
  vertices[51].get()->connectedEdges.emplace_back(edges[66].get());
  vertices[51].get()->connectedEdges.emplace_back(edges[68].get());
  vertices[52].get()->connectedEdges.emplace_back(edges[69].get());
  vertices[52].get()->connectedEdges.emplace_back(edges[71].get());
  vertices[53].get()->connectedEdges.emplace_back(edges[70].get());
  vertices[53].get()->connectedEdges.emplace_back(edges[71].get());

  // instantiating ResourceTiles
  for (int i = 0; i < 19; i++)
  {
    tiles.emplace_back(std::make_unique<ResourceTile>(i, false));
  }

  // adding observers
  tiles[0].get()->attach(vertices[0].get());
  tiles[0].get()->attach(vertices[1].get());
  tiles[0].get()->attach(vertices[3].get());
  tiles[0].get()->attach(vertices[4].get());
  tiles[0].get()->attach(vertices[8].get());
  tiles[0].get()->attach(vertices[9].get());
  tiles[1].get()->attach(vertices[2].get());
  tiles[1].get()->attach(vertices[3].get());
  tiles[1].get()->attach(vertices[7].get());
  tiles[1].get()->attach(vertices[8].get());
  tiles[1].get()->attach(vertices[13].get());
  tiles[1].get()->attach(vertices[14].get());
  tiles[2].get()->attach(vertices[4].get());
  tiles[2].get()->attach(vertices[5].get());
  tiles[2].get()->attach(vertices[9].get());
  tiles[2].get()->attach(vertices[10].get());
  tiles[2].get()->attach(vertices[15].get());
  tiles[2].get()->attach(vertices[16].get());
  tiles[3].get()->attach(vertices[6].get());
  tiles[3].get()->attach(vertices[7].get());
  tiles[3].get()->attach(vertices[12].get());
  tiles[3].get()->attach(vertices[13].get());
  tiles[3].get()->attach(vertices[18].get());
  tiles[3].get()->attach(vertices[19].get());
  tiles[4].get()->attach(vertices[8].get());
  tiles[4].get()->attach(vertices[9].get());
  tiles[4].get()->attach(vertices[14].get());
  tiles[4].get()->attach(vertices[15].get());
  tiles[4].get()->attach(vertices[20].get());
  tiles[4].get()->attach(vertices[21].get());
  tiles[5].get()->attach(vertices[10].get());
  tiles[5].get()->attach(vertices[11].get());
  tiles[5].get()->attach(vertices[16].get());
  tiles[5].get()->attach(vertices[17].get());
  tiles[5].get()->attach(vertices[22].get());
  tiles[5].get()->attach(vertices[23].get());
  tiles[6].get()->attach(vertices[13].get());
  tiles[6].get()->attach(vertices[14].get());
  tiles[6].get()->attach(vertices[19].get());
  tiles[6].get()->attach(vertices[20].get());
  tiles[6].get()->attach(vertices[25].get());
  tiles[6].get()->attach(vertices[26].get());
  tiles[7].get()->attach(vertices[15].get());
  tiles[7].get()->attach(vertices[16].get());
  tiles[7].get()->attach(vertices[21].get());
  tiles[7].get()->attach(vertices[22].get());
  tiles[7].get()->attach(vertices[27].get());
  tiles[7].get()->attach(vertices[28].get());
  tiles[8].get()->attach(vertices[18].get());
  tiles[8].get()->attach(vertices[19].get());
  tiles[8].get()->attach(vertices[24].get());
  tiles[8].get()->attach(vertices[25].get());
  tiles[8].get()->attach(vertices[30].get());
  tiles[8].get()->attach(vertices[31].get());
  tiles[9].get()->attach(vertices[20].get());
  tiles[9].get()->attach(vertices[21].get());
  tiles[9].get()->attach(vertices[26].get());
  tiles[9].get()->attach(vertices[27].get());
  tiles[9].get()->attach(vertices[32].get());
  tiles[9].get()->attach(vertices[33].get());
  tiles[10].get()->attach(vertices[22].get());
  tiles[10].get()->attach(vertices[23].get());
  tiles[10].get()->attach(vertices[28].get());
  tiles[10].get()->attach(vertices[29].get());
  tiles[10].get()->attach(vertices[34].get());
  tiles[10].get()->attach(vertices[35].get());
  tiles[11].get()->attach(vertices[25].get());
  tiles[11].get()->attach(vertices[26].get());
  tiles[11].get()->attach(vertices[31].get());
  tiles[11].get()->attach(vertices[32].get());
  tiles[11].get()->attach(vertices[37].get());
  tiles[11].get()->attach(vertices[38].get());
  tiles[12].get()->attach(vertices[27].get());
  tiles[12].get()->attach(vertices[28].get());
  tiles[12].get()->attach(vertices[33].get());
  tiles[12].get()->attach(vertices[34].get());
  tiles[12].get()->attach(vertices[39].get());
  tiles[12].get()->attach(vertices[40].get());
  tiles[13].get()->attach(vertices[30].get());
  tiles[13].get()->attach(vertices[31].get());
  tiles[13].get()->attach(vertices[36].get());
  tiles[13].get()->attach(vertices[37].get());
  tiles[13].get()->attach(vertices[42].get());
  tiles[13].get()->attach(vertices[43].get());
  tiles[14].get()->attach(vertices[32].get());
  tiles[14].get()->attach(vertices[33].get());
  tiles[14].get()->attach(vertices[38].get());
  tiles[14].get()->attach(vertices[39].get());
  tiles[14].get()->attach(vertices[44].get());
  tiles[14].get()->attach(vertices[45].get());
  tiles[15].get()->attach(vertices[34].get());
  tiles[15].get()->attach(vertices[35].get());
  tiles[15].get()->attach(vertices[40].get());
  tiles[15].get()->attach(vertices[41].get());
  tiles[15].get()->attach(vertices[46].get());
  tiles[15].get()->attach(vertices[47].get());
  tiles[16].get()->attach(vertices[37].get());
  tiles[16].get()->attach(vertices[38].get());
  tiles[16].get()->attach(vertices[43].get());
  tiles[16].get()->attach(vertices[44].get());
  tiles[16].get()->attach(vertices[48].get());
  tiles[16].get()->attach(vertices[49].get());
  tiles[17].get()->attach(vertices[39].get());
  tiles[17].get()->attach(vertices[40].get());
  tiles[17].get()->attach(vertices[45].get());
  tiles[17].get()->attach(vertices[46].get());
  tiles[17].get()->attach(vertices[50].get());
  tiles[17].get()->attach(vertices[51].get());
  tiles[18].get()->attach(vertices[44].get());
  tiles[18].get()->attach(vertices[45].get());
  tiles[18].get()->attach(vertices[49].get());
  tiles[18].get()->attach(vertices[50].get());
  tiles[18].get()->attach(vertices[52].get());
  tiles[18].get()->attach(vertices[53].get());

  std::vector<int> v = {0, 0, 0, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5};

  std::default_random_engine rng{seed};

  for (int i = 0; i < 1000; i++)
  {
    std::shuffle(v.begin(), v.end(), rng);
  }


  for (int i = 0; i < 19; i++)
  {
    if (v[i] == 0)
    {
      tiles[i].get()->type = ResourceType::BRICK;
    }

    if (v[i] == 1)
    {
      tiles[i].get()->type = ResourceType::ENERGY;
    }
    if (v[i] == 2)
    {
      tiles[i].get()->type = ResourceType::GLASS;
    }

    if (v[i] == 3)
    {
      tiles[i].get()->type = ResourceType::HEAT;
    }

    if (v[i] == 4)
    {
      tiles[i].get()->type = ResourceType::WIFI;
    }

    if (v[i] == 5)
    {
      tiles[i].get()->type = ResourceType::PARK;
    }
  }

  // initializing resourceTile values
  std::vector<int> tileV = {2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};
  
  for (int i = 0; i < 1000; i++)
  {
    std::shuffle(tileV.begin(), tileV.end(), rng);
  }

  bool seenPark = false;

  for ( int i = 0; i < 19; i++ ) {
    if (seenPark) {
      tiles[i].get()->value = tileV[i - 1];
    } else if ( tiles[i].get()->type == ResourceType::PARK ) {
      tiles[i].get()->value = 7;
      seenPark = true;
    } else {
      tiles[i].get()->value = tileV[i];
    }
  }
}

Board::Board(std::istream &boardStream)
{
  gooseLocation = nullptr;
  // vertices instantiation
  for (int i = 0; i < 54; i++)
  {
    vertices.emplace_back(std::make_unique<Vertex>(i));
  }

  // edge instantiation (with connected vectors)
  edges.emplace_back(std::make_unique<Edge>(0, vertices[0].get(), vertices[1].get()));
  edges.emplace_back(std::make_unique<Edge>(1, vertices[0].get(), vertices[3].get()));
  edges.emplace_back(std::make_unique<Edge>(2, vertices[1].get(), vertices[4].get()));
  edges.emplace_back(std::make_unique<Edge>(3, vertices[2].get(), vertices[3].get()));
  edges.emplace_back(std::make_unique<Edge>(4, vertices[4].get(), vertices[5].get()));
  edges.emplace_back(std::make_unique<Edge>(5, vertices[2].get(), vertices[7].get()));
  edges.emplace_back(std::make_unique<Edge>(6, vertices[3].get(), vertices[8].get()));
  edges.emplace_back(std::make_unique<Edge>(7, vertices[4].get(), vertices[9].get()));
  edges.emplace_back(std::make_unique<Edge>(8, vertices[5].get(), vertices[10].get()));
  edges.emplace_back(std::make_unique<Edge>(9, vertices[6].get(), vertices[7].get()));
  edges.emplace_back(std::make_unique<Edge>(10, vertices[8].get(), vertices[9].get()));
  edges.emplace_back(std::make_unique<Edge>(11, vertices[10].get(), vertices[11].get()));
  edges.emplace_back(std::make_unique<Edge>(12, vertices[6].get(), vertices[12].get()));
  edges.emplace_back(std::make_unique<Edge>(13, vertices[7].get(), vertices[13].get()));
  edges.emplace_back(std::make_unique<Edge>(14, vertices[8].get(), vertices[14].get()));
  edges.emplace_back(std::make_unique<Edge>(15, vertices[9].get(), vertices[15].get()));
  edges.emplace_back(std::make_unique<Edge>(16, vertices[10].get(), vertices[16].get()));
  edges.emplace_back(std::make_unique<Edge>(17, vertices[11].get(), vertices[17].get()));
  edges.emplace_back(std::make_unique<Edge>(18, vertices[13].get(), vertices[14].get()));
  edges.emplace_back(std::make_unique<Edge>(19, vertices[15].get(), vertices[16].get()));
  edges.emplace_back(std::make_unique<Edge>(20, vertices[12].get(), vertices[18].get()));
  edges.emplace_back(std::make_unique<Edge>(21, vertices[13].get(), vertices[19].get()));
  edges.emplace_back(std::make_unique<Edge>(22, vertices[14].get(), vertices[20].get()));
  edges.emplace_back(std::make_unique<Edge>(23, vertices[15].get(), vertices[21].get()));
  edges.emplace_back(std::make_unique<Edge>(24, vertices[16].get(), vertices[22].get()));
  edges.emplace_back(std::make_unique<Edge>(25, vertices[17].get(), vertices[23].get()));
  edges.emplace_back(std::make_unique<Edge>(26, vertices[18].get(), vertices[19].get()));
  edges.emplace_back(std::make_unique<Edge>(27, vertices[20].get(), vertices[21].get()));
  edges.emplace_back(std::make_unique<Edge>(28, vertices[22].get(), vertices[23].get()));
  edges.emplace_back(std::make_unique<Edge>(29, vertices[18].get(), vertices[24].get()));
  edges.emplace_back(std::make_unique<Edge>(30, vertices[19].get(), vertices[25].get()));
  edges.emplace_back(std::make_unique<Edge>(31, vertices[20].get(), vertices[26].get()));
  edges.emplace_back(std::make_unique<Edge>(32, vertices[21].get(), vertices[27].get()));
  edges.emplace_back(std::make_unique<Edge>(33, vertices[22].get(), vertices[28].get()));
  edges.emplace_back(std::make_unique<Edge>(34, vertices[23].get(), vertices[29].get()));
  edges.emplace_back(std::make_unique<Edge>(35, vertices[25].get(), vertices[26].get()));
  edges.emplace_back(std::make_unique<Edge>(36, vertices[27].get(), vertices[28].get()));
  edges.emplace_back(std::make_unique<Edge>(37, vertices[24].get(), vertices[30].get()));
  edges.emplace_back(std::make_unique<Edge>(38, vertices[25].get(), vertices[31].get()));
  edges.emplace_back(std::make_unique<Edge>(39, vertices[26].get(), vertices[32].get()));
  edges.emplace_back(std::make_unique<Edge>(40, vertices[27].get(), vertices[33].get()));
  edges.emplace_back(std::make_unique<Edge>(41, vertices[28].get(), vertices[34].get()));
  edges.emplace_back(std::make_unique<Edge>(42, vertices[29].get(), vertices[35].get()));
  edges.emplace_back(std::make_unique<Edge>(43, vertices[30].get(), vertices[31].get()));
  edges.emplace_back(std::make_unique<Edge>(44, vertices[32].get(), vertices[33].get()));
  edges.emplace_back(std::make_unique<Edge>(45, vertices[34].get(), vertices[35].get()));
  edges.emplace_back(std::make_unique<Edge>(46, vertices[30].get(), vertices[36].get()));
  edges.emplace_back(std::make_unique<Edge>(47, vertices[31].get(), vertices[37].get()));
  edges.emplace_back(std::make_unique<Edge>(48, vertices[32].get(), vertices[38].get()));
  edges.emplace_back(std::make_unique<Edge>(49, vertices[33].get(), vertices[39].get()));
  edges.emplace_back(std::make_unique<Edge>(50, vertices[34].get(), vertices[40].get()));
  edges.emplace_back(std::make_unique<Edge>(51, vertices[35].get(), vertices[41].get()));
  edges.emplace_back(std::make_unique<Edge>(52, vertices[37].get(), vertices[38].get()));
  edges.emplace_back(std::make_unique<Edge>(53, vertices[39].get(), vertices[40].get()));
  edges.emplace_back(std::make_unique<Edge>(54, vertices[36].get(), vertices[42].get()));
  edges.emplace_back(std::make_unique<Edge>(55, vertices[37].get(), vertices[43].get()));
  edges.emplace_back(std::make_unique<Edge>(56, vertices[38].get(), vertices[44].get()));
  edges.emplace_back(std::make_unique<Edge>(57, vertices[39].get(), vertices[45].get()));
  edges.emplace_back(std::make_unique<Edge>(58, vertices[40].get(), vertices[46].get()));
  edges.emplace_back(std::make_unique<Edge>(59, vertices[41].get(), vertices[47].get()));
  edges.emplace_back(std::make_unique<Edge>(60, vertices[42].get(), vertices[43].get()));
  edges.emplace_back(std::make_unique<Edge>(61, vertices[44].get(), vertices[45].get()));
  edges.emplace_back(std::make_unique<Edge>(62, vertices[46].get(), vertices[47].get()));
  edges.emplace_back(std::make_unique<Edge>(63, vertices[43].get(), vertices[48].get()));
  edges.emplace_back(std::make_unique<Edge>(64, vertices[44].get(), vertices[49].get()));
  edges.emplace_back(std::make_unique<Edge>(65, vertices[45].get(), vertices[50].get()));
  edges.emplace_back(std::make_unique<Edge>(66, vertices[46].get(), vertices[51].get()));
  edges.emplace_back(std::make_unique<Edge>(67, vertices[48].get(), vertices[49].get()));
  edges.emplace_back(std::make_unique<Edge>(68, vertices[50].get(), vertices[51].get()));
  edges.emplace_back(std::make_unique<Edge>(69, vertices[49].get(), vertices[52].get()));
  edges.emplace_back(std::make_unique<Edge>(70, vertices[50].get(), vertices[53].get()));
  edges.emplace_back(std::make_unique<Edge>(71, vertices[52].get(), vertices[53].get()));

  // connecting vertices to edges
  vertices[0].get()->connectedEdges.emplace_back(edges[0].get());
  vertices[0].get()->connectedEdges.emplace_back(edges[1].get());
  vertices[1].get()->connectedEdges.emplace_back(edges[0].get());
  vertices[1].get()->connectedEdges.emplace_back(edges[2].get());
  vertices[2].get()->connectedEdges.emplace_back(edges[3].get());
  vertices[2].get()->connectedEdges.emplace_back(edges[5].get());
  vertices[3].get()->connectedEdges.emplace_back(edges[1].get());
  vertices[3].get()->connectedEdges.emplace_back(edges[3].get());
  vertices[3].get()->connectedEdges.emplace_back(edges[6].get());
  vertices[4].get()->connectedEdges.emplace_back(edges[2].get());
  vertices[4].get()->connectedEdges.emplace_back(edges[4].get());
  vertices[4].get()->connectedEdges.emplace_back(edges[7].get());
  vertices[5].get()->connectedEdges.emplace_back(edges[4].get());
  vertices[5].get()->connectedEdges.emplace_back(edges[8].get());
  vertices[6].get()->connectedEdges.emplace_back(edges[9].get());
  vertices[6].get()->connectedEdges.emplace_back(edges[12].get());
  vertices[7].get()->connectedEdges.emplace_back(edges[5].get());
  vertices[7].get()->connectedEdges.emplace_back(edges[9].get());
  vertices[7].get()->connectedEdges.emplace_back(edges[13].get());
  vertices[8].get()->connectedEdges.emplace_back(edges[6].get());
  vertices[8].get()->connectedEdges.emplace_back(edges[10].get());
  vertices[8].get()->connectedEdges.emplace_back(edges[14].get());
  vertices[9].get()->connectedEdges.emplace_back(edges[7].get());
  vertices[9].get()->connectedEdges.emplace_back(edges[10].get());
  vertices[9].get()->connectedEdges.emplace_back(edges[15].get());
  vertices[10].get()->connectedEdges.emplace_back(edges[8].get());
  vertices[10].get()->connectedEdges.emplace_back(edges[11].get());
  vertices[10].get()->connectedEdges.emplace_back(edges[16].get());
  vertices[11].get()->connectedEdges.emplace_back(edges[11].get());
  vertices[11].get()->connectedEdges.emplace_back(edges[17].get());
  vertices[12].get()->connectedEdges.emplace_back(edges[12].get());
  vertices[12].get()->connectedEdges.emplace_back(edges[20].get());
  vertices[13].get()->connectedEdges.emplace_back(edges[13].get());
  vertices[13].get()->connectedEdges.emplace_back(edges[18].get());
  vertices[13].get()->connectedEdges.emplace_back(edges[21].get());
  vertices[14].get()->connectedEdges.emplace_back(edges[14].get());
  vertices[14].get()->connectedEdges.emplace_back(edges[18].get());
  vertices[14].get()->connectedEdges.emplace_back(edges[22].get());
  vertices[15].get()->connectedEdges.emplace_back(edges[15].get());
  vertices[15].get()->connectedEdges.emplace_back(edges[19].get());
  vertices[15].get()->connectedEdges.emplace_back(edges[23].get());
  vertices[16].get()->connectedEdges.emplace_back(edges[16].get());
  vertices[16].get()->connectedEdges.emplace_back(edges[19].get());
  vertices[16].get()->connectedEdges.emplace_back(edges[24].get());
  vertices[17].get()->connectedEdges.emplace_back(edges[17].get());
  vertices[17].get()->connectedEdges.emplace_back(edges[25].get());
  vertices[18].get()->connectedEdges.emplace_back(edges[20].get());
  vertices[18].get()->connectedEdges.emplace_back(edges[26].get());
  vertices[18].get()->connectedEdges.emplace_back(edges[29].get());
  vertices[19].get()->connectedEdges.emplace_back(edges[21].get());
  vertices[19].get()->connectedEdges.emplace_back(edges[26].get());
  vertices[19].get()->connectedEdges.emplace_back(edges[30].get());
  vertices[20].get()->connectedEdges.emplace_back(edges[22].get());
  vertices[20].get()->connectedEdges.emplace_back(edges[27].get());
  vertices[20].get()->connectedEdges.emplace_back(edges[31].get());
  vertices[21].get()->connectedEdges.emplace_back(edges[23].get());
  vertices[21].get()->connectedEdges.emplace_back(edges[27].get());
  vertices[21].get()->connectedEdges.emplace_back(edges[32].get());
  vertices[22].get()->connectedEdges.emplace_back(edges[24].get());
  vertices[22].get()->connectedEdges.emplace_back(edges[28].get());
  vertices[22].get()->connectedEdges.emplace_back(edges[33].get());
  vertices[23].get()->connectedEdges.emplace_back(edges[25].get());
  vertices[23].get()->connectedEdges.emplace_back(edges[28].get());
  vertices[23].get()->connectedEdges.emplace_back(edges[34].get());
  vertices[24].get()->connectedEdges.emplace_back(edges[29].get());
  vertices[24].get()->connectedEdges.emplace_back(edges[37].get());
  vertices[25].get()->connectedEdges.emplace_back(edges[30].get());
  vertices[25].get()->connectedEdges.emplace_back(edges[38].get());
  vertices[26].get()->connectedEdges.emplace_back(edges[31].get());
  vertices[26].get()->connectedEdges.emplace_back(edges[35].get());
  vertices[26].get()->connectedEdges.emplace_back(edges[39].get());
  vertices[27].get()->connectedEdges.emplace_back(edges[32].get());
  vertices[27].get()->connectedEdges.emplace_back(edges[36].get());
  vertices[27].get()->connectedEdges.emplace_back(edges[40].get());
  vertices[28].get()->connectedEdges.emplace_back(edges[33].get());
  vertices[28].get()->connectedEdges.emplace_back(edges[36].get());
  vertices[28].get()->connectedEdges.emplace_back(edges[41].get());
  vertices[29].get()->connectedEdges.emplace_back(edges[34].get());
  vertices[29].get()->connectedEdges.emplace_back(edges[42].get());
  vertices[30].get()->connectedEdges.emplace_back(edges[37].get());
  vertices[30].get()->connectedEdges.emplace_back(edges[43].get());
  vertices[30].get()->connectedEdges.emplace_back(edges[46].get());
  vertices[31].get()->connectedEdges.emplace_back(edges[38].get());
  vertices[31].get()->connectedEdges.emplace_back(edges[43].get());
  vertices[31].get()->connectedEdges.emplace_back(edges[47].get());
  vertices[32].get()->connectedEdges.emplace_back(edges[39].get());
  vertices[32].get()->connectedEdges.emplace_back(edges[44].get());
  vertices[32].get()->connectedEdges.emplace_back(edges[48].get());
  vertices[33].get()->connectedEdges.emplace_back(edges[40].get());
  vertices[33].get()->connectedEdges.emplace_back(edges[44].get());
  vertices[33].get()->connectedEdges.emplace_back(edges[49].get());
  vertices[34].get()->connectedEdges.emplace_back(edges[41].get());
  vertices[34].get()->connectedEdges.emplace_back(edges[45].get());
  vertices[34].get()->connectedEdges.emplace_back(edges[50].get());
  vertices[35].get()->connectedEdges.emplace_back(edges[42].get());
  vertices[35].get()->connectedEdges.emplace_back(edges[45].get());
  vertices[35].get()->connectedEdges.emplace_back(edges[51].get());
  vertices[36].get()->connectedEdges.emplace_back(edges[46].get());
  vertices[36].get()->connectedEdges.emplace_back(edges[54].get());
  vertices[37].get()->connectedEdges.emplace_back(edges[47].get());
  vertices[37].get()->connectedEdges.emplace_back(edges[52].get());
  vertices[37].get()->connectedEdges.emplace_back(edges[55].get());
  vertices[38].get()->connectedEdges.emplace_back(edges[48].get());
  vertices[38].get()->connectedEdges.emplace_back(edges[52].get());
  vertices[38].get()->connectedEdges.emplace_back(edges[56].get());
  vertices[39].get()->connectedEdges.emplace_back(edges[49].get());
  vertices[39].get()->connectedEdges.emplace_back(edges[53].get());
  vertices[39].get()->connectedEdges.emplace_back(edges[57].get());
  vertices[40].get()->connectedEdges.emplace_back(edges[50].get());
  vertices[40].get()->connectedEdges.emplace_back(edges[53].get());
  vertices[40].get()->connectedEdges.emplace_back(edges[58].get());
  vertices[41].get()->connectedEdges.emplace_back(edges[51].get());
  vertices[41].get()->connectedEdges.emplace_back(edges[59].get());
  vertices[42].get()->connectedEdges.emplace_back(edges[54].get());
  vertices[42].get()->connectedEdges.emplace_back(edges[60].get());
  vertices[43].get()->connectedEdges.emplace_back(edges[55].get());
  vertices[43].get()->connectedEdges.emplace_back(edges[60].get());
  vertices[43].get()->connectedEdges.emplace_back(edges[63].get());
  vertices[44].get()->connectedEdges.emplace_back(edges[56].get());
  vertices[44].get()->connectedEdges.emplace_back(edges[61].get());
  vertices[44].get()->connectedEdges.emplace_back(edges[64].get());
  vertices[45].get()->connectedEdges.emplace_back(edges[57].get());
  vertices[45].get()->connectedEdges.emplace_back(edges[61].get());
  vertices[45].get()->connectedEdges.emplace_back(edges[64].get());
  vertices[45].get()->connectedEdges.emplace_back(edges[57].get());
  vertices[45].get()->connectedEdges.emplace_back(edges[61].get());
  vertices[45].get()->connectedEdges.emplace_back(edges[65].get());
  vertices[46].get()->connectedEdges.emplace_back(edges[58].get());
  vertices[46].get()->connectedEdges.emplace_back(edges[62].get());
  vertices[46].get()->connectedEdges.emplace_back(edges[66].get());
  vertices[47].get()->connectedEdges.emplace_back(edges[59].get());
  vertices[47].get()->connectedEdges.emplace_back(edges[62].get());
  vertices[48].get()->connectedEdges.emplace_back(edges[63].get());
  vertices[48].get()->connectedEdges.emplace_back(edges[67].get());
  vertices[49].get()->connectedEdges.emplace_back(edges[64].get());
  vertices[49].get()->connectedEdges.emplace_back(edges[67].get());
  vertices[49].get()->connectedEdges.emplace_back(edges[69].get());
  vertices[50].get()->connectedEdges.emplace_back(edges[65].get());
  vertices[50].get()->connectedEdges.emplace_back(edges[68].get());
  vertices[50].get()->connectedEdges.emplace_back(edges[70].get());
  vertices[51].get()->connectedEdges.emplace_back(edges[66].get());
  vertices[51].get()->connectedEdges.emplace_back(edges[68].get());
  vertices[52].get()->connectedEdges.emplace_back(edges[69].get());
  vertices[52].get()->connectedEdges.emplace_back(edges[71].get());
  vertices[53].get()->connectedEdges.emplace_back(edges[70].get());
  vertices[53].get()->connectedEdges.emplace_back(edges[71].get());

  // instantiating ResourceTiles
  for (int i = 0; i < 19; i++)
  {
    tiles.emplace_back(std::make_unique<ResourceTile>(i, false));
  }

  // adding observers
  tiles[0].get()->attach(vertices[0].get());
  tiles[0].get()->attach(vertices[1].get());
  tiles[0].get()->attach(vertices[3].get());
  tiles[0].get()->attach(vertices[4].get());
  tiles[0].get()->attach(vertices[8].get());
  tiles[0].get()->attach(vertices[9].get());
  tiles[1].get()->attach(vertices[2].get());
  tiles[1].get()->attach(vertices[3].get());
  tiles[1].get()->attach(vertices[7].get());
  tiles[1].get()->attach(vertices[8].get());
  tiles[1].get()->attach(vertices[13].get());
  tiles[1].get()->attach(vertices[14].get());
  tiles[2].get()->attach(vertices[4].get());
  tiles[2].get()->attach(vertices[5].get());
  tiles[2].get()->attach(vertices[9].get());
  tiles[2].get()->attach(vertices[10].get());
  tiles[2].get()->attach(vertices[15].get());
  tiles[2].get()->attach(vertices[16].get());
  tiles[3].get()->attach(vertices[6].get());
  tiles[3].get()->attach(vertices[7].get());
  tiles[3].get()->attach(vertices[12].get());
  tiles[3].get()->attach(vertices[13].get());
  tiles[3].get()->attach(vertices[18].get());
  tiles[3].get()->attach(vertices[19].get());
  tiles[4].get()->attach(vertices[8].get());
  tiles[4].get()->attach(vertices[9].get());
  tiles[4].get()->attach(vertices[14].get());
  tiles[4].get()->attach(vertices[15].get());
  tiles[4].get()->attach(vertices[20].get());
  tiles[4].get()->attach(vertices[21].get());
  tiles[5].get()->attach(vertices[10].get());
  tiles[5].get()->attach(vertices[11].get());
  tiles[5].get()->attach(vertices[16].get());
  tiles[5].get()->attach(vertices[17].get());
  tiles[5].get()->attach(vertices[22].get());
  tiles[5].get()->attach(vertices[23].get());
  tiles[6].get()->attach(vertices[13].get());
  tiles[6].get()->attach(vertices[14].get());
  tiles[6].get()->attach(vertices[19].get());
  tiles[6].get()->attach(vertices[20].get());
  tiles[6].get()->attach(vertices[25].get());
  tiles[6].get()->attach(vertices[26].get());
  tiles[7].get()->attach(vertices[15].get());
  tiles[7].get()->attach(vertices[16].get());
  tiles[7].get()->attach(vertices[21].get());
  tiles[7].get()->attach(vertices[22].get());
  tiles[7].get()->attach(vertices[27].get());
  tiles[7].get()->attach(vertices[28].get());
  tiles[8].get()->attach(vertices[18].get());
  tiles[8].get()->attach(vertices[19].get());
  tiles[8].get()->attach(vertices[24].get());
  tiles[8].get()->attach(vertices[25].get());
  tiles[8].get()->attach(vertices[30].get());
  tiles[8].get()->attach(vertices[31].get());
  tiles[9].get()->attach(vertices[20].get());
  tiles[9].get()->attach(vertices[21].get());
  tiles[9].get()->attach(vertices[26].get());
  tiles[9].get()->attach(vertices[27].get());
  tiles[9].get()->attach(vertices[32].get());
  tiles[9].get()->attach(vertices[33].get());
  tiles[10].get()->attach(vertices[22].get());
  tiles[10].get()->attach(vertices[23].get());
  tiles[10].get()->attach(vertices[28].get());
  tiles[10].get()->attach(vertices[29].get());
  tiles[10].get()->attach(vertices[34].get());
  tiles[10].get()->attach(vertices[35].get());
  tiles[11].get()->attach(vertices[25].get());
  tiles[11].get()->attach(vertices[26].get());
  tiles[11].get()->attach(vertices[31].get());
  tiles[11].get()->attach(vertices[32].get());
  tiles[11].get()->attach(vertices[37].get());
  tiles[11].get()->attach(vertices[38].get());
  tiles[12].get()->attach(vertices[27].get());
  tiles[12].get()->attach(vertices[28].get());
  tiles[12].get()->attach(vertices[33].get());
  tiles[12].get()->attach(vertices[34].get());
  tiles[12].get()->attach(vertices[39].get());
  tiles[12].get()->attach(vertices[40].get());
  tiles[13].get()->attach(vertices[30].get());
  tiles[13].get()->attach(vertices[31].get());
  tiles[13].get()->attach(vertices[36].get());
  tiles[13].get()->attach(vertices[37].get());
  tiles[13].get()->attach(vertices[42].get());
  tiles[13].get()->attach(vertices[43].get());
  tiles[14].get()->attach(vertices[32].get());
  tiles[14].get()->attach(vertices[33].get());
  tiles[14].get()->attach(vertices[38].get());
  tiles[14].get()->attach(vertices[39].get());
  tiles[14].get()->attach(vertices[44].get());
  tiles[14].get()->attach(vertices[45].get());
  tiles[15].get()->attach(vertices[34].get());
  tiles[15].get()->attach(vertices[35].get());
  tiles[15].get()->attach(vertices[40].get());
  tiles[15].get()->attach(vertices[41].get());
  tiles[15].get()->attach(vertices[46].get());
  tiles[15].get()->attach(vertices[47].get());
  tiles[16].get()->attach(vertices[37].get());
  tiles[16].get()->attach(vertices[38].get());
  tiles[16].get()->attach(vertices[43].get());
  tiles[16].get()->attach(vertices[44].get());
  tiles[16].get()->attach(vertices[48].get());
  tiles[16].get()->attach(vertices[49].get());
  tiles[17].get()->attach(vertices[39].get());
  tiles[17].get()->attach(vertices[40].get());
  tiles[17].get()->attach(vertices[45].get());
  tiles[17].get()->attach(vertices[46].get());
  tiles[17].get()->attach(vertices[50].get());
  tiles[17].get()->attach(vertices[51].get());
  tiles[18].get()->attach(vertices[44].get());
  tiles[18].get()->attach(vertices[45].get());
  tiles[18].get()->attach(vertices[49].get());
  tiles[18].get()->attach(vertices[50].get());
  tiles[18].get()->attach(vertices[52].get());
  tiles[18].get()->attach(vertices[53].get());

  //TODO: throw exceptions

  for (int i = 0; i < 19; i++)
  {
    string temp;
    int resourceIndex;
    int resourceValue;

    try {
      boardStream >> temp;
      resourceIndex = stoi(temp);
      temp = "";
      boardStream >> temp;
      resourceValue = stoi(temp);
    } catch (invalid_argument &e) {
       throw invalid_argument{"File has an invalid format."};
      }

    if (resourceValue > 12 || resourceValue < 2) {
      throw invalid_argument{"File has an invalid format."};
    }

    switch (resourceIndex)
    {
    case 0:
      tiles[i].get()->type = ResourceType::BRICK;
      break;
    case 1:
      tiles[i].get()->type = ResourceType::ENERGY;
      break;
    case 2:
      tiles[i].get()->type = ResourceType::GLASS;
      break;
    case 3:
      tiles[i].get()->type = ResourceType::HEAT;
      break;
    case 4:
      tiles[i].get()->type = ResourceType::WIFI;
      break;
    case 5:
      tiles[i].get()->type = ResourceType::PARK;
      break;
    default:
      throw invalid_argument{"Invalid tile detected in load board file."};
      break;
    }
    if (resourceValue == 7) {
      if (resourceIndex != 5) {
        throw invalid_argument{"Cannot initialize board. Resource tile cannot have value of 7."};
      }
    }
    tiles[i].get()->value = resourceValue;
  }
}

void Board::moveGooseTo(ResourceTile &tile)
{
  if (&tile == gooseLocation)
  {
    throw invalid_argument{"Goose is already at this location. Move is not allowed."};
  }

  tile.hasGoose = true;

  if(gooseLocation){
      gooseLocation->hasGoose = false;
  }

  gooseLocation = &tile;
}

void Board::activateResourceTile(const int rollNumber)
{
  for (auto &tile : tiles)
  {
    if (tile->value == rollNumber)
    {
      tile->giveResourceIfNoGoose();
    }
  }
}

void Board::addRoad(const unsigned int location, Player &builder)
{
  if (location > edges.size() - 1)
  {
    throw invalid_argument{"You cannot build here."};
  }

  if (builder.status.numHeat < 1 || builder.status.numWifi < 1)
  {
    throw invalid_argument{"You do not have enough resources."};
  }

  Edge *edge = edges.at(location).get();

  if (edge->canBuildRoad(builder))
  {
    builder.status.numHeat -= 1;
    builder.status.numWifi -= 1;
    edge->owner = &builder;
    builder.status.ownedRoads.insert(pair<int, Edge *>(location, edge));
  }
  else
  {
    throw invalid_argument{"You cannot build here."};
  }
}

void Board::addResidence(const unsigned int location, Player &builder, bool isNewGame)
{
  if (location > vertices.size() - 1)
  {
    throw invalid_argument{"You cannot build here."};
  }

  if ((builder.status.numEnergies < 1 || builder.status.numWifi < 1 || builder.status.numBricks < 1 || builder.status.numGlass < 1) && (!isNewGame))
  {
    throw invalid_argument{"You do not have enough resources."};
  }

  Vertex *vertex = vertices.at(location).get();

  if (vertex->canBuild(builder, isNewGame))
  {
    vertex->owner = &builder;
    vertex->type = VertexType::BASEMENT;
    if (!isNewGame)
    {
      builder.status.numWifi -= 1;
      builder.status.numBricks -= 1;
      builder.status.numGlass -= 1;
      builder.status.numEnergies -= 1;
    }

    builder.status.ownedBuildings.insert(pair<int, Vertex *>(location, vertex));
  }
  else
  {
    throw invalid_argument{"Unable to build basement. Must meet the two conditions for building a residence."};
  }
}

void Board::improveResidence(const unsigned int location, Player &builder)
{
  if (location > vertices.size() - 1)
  {
    throw invalid_argument{"Invalid location"};
  }
  Vertex *vertex = vertices.at(location).get();

  if (vertex->canUpgrade(builder))
  {
    if (vertex->type == VertexType::BASEMENT)
    {
      vertex->type = VertexType::HOUSE;
      builder.status.numGlass -= 2;
      builder.status.numHeat -= 3;
    }
    else if (vertex->type == VertexType::HOUSE)
    {
      vertex->type = VertexType::TOWER;
      builder.status.numGlass -= 2;
      builder.status.numHeat -= 2;
      builder.status.numWifi -= 1;
      builder.status.numBricks -= 3;
      builder.status.numEnergies -= 2;
    }
  }
  else
  {

    if (vertex->type == VertexType::BASEMENT)
    {
      if (builder.status.numGlass < 2 && builder.status.numHeat < 3)
      {
        throw invalid_argument{"You do not have enough resources."};
      }
    }
    if (vertex->type == VertexType::HOUSE)
    {
      if (builder.status.numBricks < 3 && builder.status.numEnergies < 2 &&
          builder.status.numGlass < 2 && builder.status.numWifi < 1 && builder.status.numHeat < 2)
      {
        throw invalid_argument{"You do not have enough resources."};
      }
    }

    throw invalid_argument{"You cannot improve here."};
  }
}

// needs to be tested
string Board::getSerializedBoard()
{
  string s = "";

  for (int i = 0; i < 19; i++)
  {
    if (tiles[i].get()->type == ResourceType::BRICK)
    {
      s += "0 ";
    }

    if (tiles[i].get()->type == ResourceType::ENERGY)
    {
      s += "1 ";
    }
    if (tiles[i].get()->type == ResourceType::GLASS)
    {
      s += "2 ";
    }

    if (tiles[i].get()->type == ResourceType::HEAT)
    {
      s += "3 ";
    }

    if (tiles[i].get()->type == ResourceType::WIFI)
    {
      s += "4 ";
    }

    if (tiles[i].get()->type == ResourceType::PARK)
    {
      s += "5 7";
      if ( i == 18 ) { 
        continue;
      } else {
        s += " ";
        continue;
      }
    }
    if ( i == 18 ) {
      s += std::to_string(tiles[i].get()->value);
    } else {
      s += std::to_string(tiles[i].get()->value);
      s += " ";
    }

  }

  return s;
};

string Board::getSerializedGooseLocation()
{
  if(gooseLocation){
    return to_string(gooseLocation->location);
  }else{
    return "-1";
  }
  
}
