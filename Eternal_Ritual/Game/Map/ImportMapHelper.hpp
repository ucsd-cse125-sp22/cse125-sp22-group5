//
//  ImportMapHelper.hpp
//
//  Created by Kangming Yu on 5/15/22.
//

#ifndef ImportMapHelper_hpp
#define ImportMapHelper_hpp

#include <vector>

#include "KGLEngine/Engine.hpp"
#include "Game/Map/MapSystemManager.hpp"


namespace ImportMapHelper {

void importMapBox(std::vector<MapBoxObject*>& cgUsedBox);
void importMapModel(std::vector<Node*>& cgUsedNode);
void importTestMap();

} // namespace ImportMapHelper




#endif /* ImportMapHelper_hpp */
