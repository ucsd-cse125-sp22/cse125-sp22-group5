//
//  ImportMapHelper.cpp
//
//  Created by Kangming Yu on 5/15/22.
//

#include "Game/Map/ImportMapHelper.hpp"

#include <glm/glm.hpp>

#include "Game/Map/MapSystemManager.hpp"
#include "KGLEngine/Engine.hpp"

using namespace glm;


namespace ImportMapHelper {

void importMapBox() {
    unsigned int boxType;
    vec3 boxSize, boxPosition, boxEulerAngles;
    
    boxType = 1;
    boxSize = vec3(20.0f, 20.0f, 20.0f);
    boxPosition = vec3(0.0f, 9.0f, 60.0f);
    boxEulerAngles = vec3(0.0f, -0.0f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 0;
    boxSize = vec3(20.0f, 1.0f, 40.0f);
    boxPosition = vec3(0.0f, -1.5f, 30.0f);
    boxEulerAngles = vec3(0.0f, -0.0f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 0;
    boxSize = vec3(100.0f, 1.0f, 20.0f);
    boxPosition = vec3(0.0f, -1.5f, 0.0f);
    boxEulerAngles = vec3(0.0f, -0.0f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 0;
    boxSize = vec3(20.0f, 1.0f, 40.0f);
    boxPosition = vec3(0.0f, -1.5f, -30.0f);
    boxEulerAngles = vec3(0.0f, -0.0f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 0;
    boxSize = vec3(20.0f, 1.0f, 20.0f);
    boxPosition = vec3(36.339744567871094f, -1.5f, 13.65999984741211f);
    boxEulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 0;
    boxSize = vec3(20.0f, 1.0f, 20.0f);
    boxPosition = vec3(26.200000762939453f, -1.5f, 27.0f);
    boxEulerAngles = vec3(0.0f, 45.00000466733367f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 0;
    boxSize = vec3(19.999998092651367f, 1.0f, 20.0f);
    boxPosition = vec3(13.65999984741211f, -1.5f, 36.34000015258789f);
    boxEulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 0;
    boxSize = vec3(20.0f, 1.0f, 20.0f);
    boxPosition = vec3(20.0f, -1.5f, 20.0f);
    boxEulerAngles = vec3(0.0f, -0.0f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 0;
    boxSize = vec3(19.999998092651367f, 1.0f, 20.0f);
    boxPosition = vec3(-13.600000381469727f, -1.5f, -36.33000183105469f);
    boxEulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 0;
    boxSize = vec3(20.0f, 1.0f, 20.0f);
    boxPosition = vec3(-36.34000015258789f, -1.5f, -13.600000381469727f);
    boxEulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 0;
    boxSize = vec3(20.0f, 1.0f, 20.0f);
    boxPosition = vec3(-26.95877456665039f, -1.5f, -26.158771514892578f);
    boxEulerAngles = vec3(0.0f, 45.00000466733367f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 0;
    boxSize = vec3(20.0f, 1.0f, 20.0f);
    boxPosition = vec3(-20.0f, -1.5f, -20.0f);
    boxEulerAngles = vec3(0.0f, -0.0f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 0;
    boxSize = vec3(20.0f, 1.0f, 20.0f);
    boxPosition = vec3(20.0f, -1.5f, -20.0f);
    boxEulerAngles = vec3(0.0f, -0.0f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 0;
    boxSize = vec3(20.0f, 1.0f, 20.0f);
    boxPosition = vec3(-20.0f, -1.5f, 20.0f);
    boxEulerAngles = vec3(0.0f, -0.0f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 0;
    boxSize = vec3(19.999998092651367f, 1.0f, 20.0f);
    boxPosition = vec3(-13.731363296508789f, -1.5f, 36.58491516113281f);
    boxEulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 0;
    boxSize = vec3(19.999998092651367f, 1.0f, 20.0f);
    boxPosition = vec3(-36.34000015258789f, -1.5f, 13.601505279541016f);
    boxEulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 0;
    boxSize = vec3(20.0f, 1.0f, 20.0f);
    boxPosition = vec3(-26.481189727783203f, -1.5f, 26.653076171875f);
    boxEulerAngles = vec3(0.0f, 45.00000466733367f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 0;
    boxSize = vec3(19.999998092651367f, 1.0f, 20.0f);
    boxPosition = vec3(13.596307754516602f, -1.5f, -36.33232116699219f);
    boxEulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 0;
    boxSize = vec3(20.0f, 1.0f, 20.0f);
    boxPosition = vec3(26.81570053100586f, -1.5f, -26.241455078125f);
    boxEulerAngles = vec3(0.0f, 45.00000466733367f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 0;
    boxSize = vec3(19.999998092651367f, 1.0f, 20.0f);
    boxPosition = vec3(36.2993278503418f, -1.5f, -13.646175384521484f);
    boxEulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(20.0f, 20.0f, 20.0f);
    boxPosition = vec3(0.0f, 9.0f, -60.0f);
    boxEulerAngles = vec3(0.0f, -0.0f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(5.0f, 30.0f, 20.0f);
    boxPosition = vec3(-19.679931640625f, 13.0f, 47.426387786865234f);
    boxEulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(5.0f, 30.0f, 20.0f);
    boxPosition = vec3(-35.30475616455078f, 13.0f, 35.362510681152344f);
    boxEulerAngles = vec3(0.0f, 44.999994422049916f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(20.0f, 30.0f, 5.0f);
    boxPosition = vec3(-47.292022705078125f, 13.0f, 19.538402557373047f);
    boxEulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(19.9999942779541f, 30.0f, 4.999998569488525f);
    boxPosition = vec3(-52.50025177001953f, 13.0f, -0.058162689208984375f);
    boxEulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(20.0f, 30.0f, 5.0f);
    boxPosition = vec3(-47.196224212646484f, 13.0f, -19.518991470336914f);
    boxEulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(5.0f, 30.0f, 20.0f);
    boxPosition = vec3(-35.77626037597656f, 13.0f, -34.86589431762695f);
    boxEulerAngles = vec3(0.0f, -44.999994422049916f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(5.0f, 30.0f, 20.0f);
    boxPosition = vec3(-19.81863021850586f, 13.0f, -47.04525375366211f);
    boxEulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(5.0f, 30.0f, 5.0f);
    boxPosition = vec3(14.256914138793945f, 14.0f, 40.71234130859375f);
    boxEulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(29.999935150146484f, 2.999999523162842f, 16.999998092651367f);
    boxPosition = vec3(-36.28617477416992f, -1.132124423980713f, -18.673717498779297f);
    boxEulerAngles = vec3(9.99999970909292f, 60.00000849984128f, -1.707547699614187e-06f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(5.0f, 30.0f, 5.0f);
    boxPosition = vec3(27.738876342773438f, 14.0f, 30.06119155883789f);
    boxEulerAngles = vec3(0.0f, -44.999994422049916f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(5.0f, 7.0f, 5.0f);
    boxPosition = vec3(27.201324462890625f, 2.5f, -26.600440979003906f);
    boxEulerAngles = vec3(0.0f, 44.999994422049916f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(9.999994277954102f, 2.5f, 14.99999713897705f);
    boxPosition = vec3(-19.002153396606445f, 0.24999995529651642f, 24.259979248046875f);
    boxEulerAngles = vec3(0.0f, 59.99999483946294f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(4.999887943267822f, 4.999917030334473f, 22.999780654907227f);
    boxPosition = vec3(34.57914733886719f, 2.5202579498291016f, -17.966392517089844f);
    boxEulerAngles = vec3(13.46300038716412f, 38.7630003512636f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(9.999835968017578f, 2.499964952468872f, 14.999848365783691f);
    boxPosition = vec3(12.881000518798828f, 0.24999994039535522f, -10.011907577514648f);
    boxEulerAngles = vec3(0.0f, -69.99999967119774f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(4.999978542327881f, 3.000000238418579f, 17.00000762939453f);
    boxPosition = vec3(-5.298661231994629f, -1.336275339126587f, 31.8536376953125f);
    boxEulerAngles = vec3(8.999993420258647f, 60.00000849984128f, -5.122643913064559e-06f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(0.5f, 2.0f, 5.0f);
    boxPosition = vec3(10.21187973022461f, 0.0f, 21.193662643432617f);
    boxEulerAngles = vec3(0.0f, -0.0f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(0.4999998211860657f, 1.0f, 9.99999713897705f);
    boxPosition = vec3(25.113908767700195f, -0.5f, 11.59774398803711f);
    boxEulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 2;
    boxSize = vec3(0.5f, 1.0f, 10.0f);
    boxPosition = vec3(4.626926422119141f, -0.5f, 7.29351806640625f);
    boxEulerAngles = vec3(0.0f, -0.0f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(5.000000953674316f, 3.0f, 17.0f);
    boxPosition = vec3(5.108200550079346f, -1.3108752965927124f, -21.101150512695312f);
    boxEulerAngles = vec3(-9.000000250447817f, 19.99999771063855f, 5.6785429905125e-07f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 2;
    boxSize = vec3(0.5f, 2.0f, 10.0f);
    boxPosition = vec3(-6.175685882568359f, 0.0f, -4.580935478210449f);
    boxEulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(0.5f, 2.0f, 7.0f);
    boxPosition = vec3(-10.48333740234375f, 0.0f, 9.90719985961914f);
    boxEulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(0.4999997913837433f, 1.0f, 3.999999761581421f);
    boxPosition = vec3(2.3769264221191406f, -0.5f, 6.538968086242676f);
    boxEulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(0.5f, 2.0f, 5.0f);
    boxPosition = vec3(-9.59457778930664f, 0.0f, -1.830935001373291f);
    boxEulerAngles = vec3(0.0f, -0.0f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 2;
    boxSize = vec3(4.9999680519104f, 0.9999958872795105f, 6.999967098236084f);
    boxPosition = vec3(-12.002592086791992f, -0.4999999701976776f, -18.14734649658203f);
    boxEulerAngles = vec3(0.0f, 33.53639957949186f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 2;
    boxSize = vec3(2.9999992847442627f, 2.0f, 3.9999990463256836f);
    boxPosition = vec3(-7.776100158691406f, 0.0f, -15.409856796264648f);
    boxEulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 2;
    boxSize = vec3(4.999841690063477f, 4.0f, 5.0f);
    boxPosition = vec3(40.72988510131836f, 0.9999867081642151f, 2.3642375469207764f);
    boxEulerAngles = vec3(179.999991348578f, 20.135100559968695f, 179.999991348578f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 2;
    boxSize = vec3(4.999831199645996f, 3.0f, 4.9999918937683105f);
    boxPosition = vec3(39.35308837890625f, 0.5000176429748535f, 7.0984416007995605f);
    boxEulerAngles = vec3(179.999991348578f, -14.096251130778096f, 179.999991348578f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 2;
    boxSize = vec3(4.999912738800049f, 4.0f, 5.00007438659668f);
    boxPosition = vec3(39.572853088378906f, 0.9999866485595703f, 11.962966918945312f);
    boxEulerAngles = vec3(179.999991348578f, -71.10730310925103f, 179.999991348578f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 2;
    boxSize = vec3(3.0f, 2.999999761581421f, 3.0f);
    boxPosition = vec3(-13.633177757263184f, 2.999999761581421f, 23.612285614013672f);
    boxEulerAngles = vec3(179.999991348578f, -71.10728261868353f, 179.999991348578f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 2;
    boxSize = vec3(1.0000003576278687f, 1.0f, 1.0000003576278687f);
    boxPosition = vec3(-21.799108505249023f, 2.0f, 18.328943252563477f);
    boxEulerAngles = vec3(179.999991348578f, -23.733391063798567f, 179.999991348578f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 2;
    boxSize = vec3(1.0000003576278687f, 1.0f, 1.0000003576278687f);
    boxPosition = vec3(-21.782814025878906f, 2.0f, 18.312650680541992f);
    boxEulerAngles = vec3(179.999991348578f, -23.73339277134586f, 179.999991348578f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 2;
    boxSize = vec3(1.0000003576278687f, 1.0f, 1.0000003576278687f);
    boxPosition = vec3(-21.2570743560791f, 2.0f, 19.338041305541992f);
    boxEulerAngles = vec3(179.999991348578f, -23.733394478893153f, 179.999991348578f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 2;
    boxSize = vec3(1.0000003576278687f, 0.9999999403953552f, 1.0000003576278687f);
    boxPosition = vec3(-19.967870712280273f, 1.9999998807907104f, 19.419044494628906f);
    boxEulerAngles = vec3(179.999991348578f, -23.73339277134586f, 179.999991348578f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 2;
    boxSize = vec3(1.0000003576278687f, 1.0f, 1.0000003576278687f);
    boxPosition = vec3(-18.6903018951416f, 2.0f, 20.22953224182129f);
    boxEulerAngles = vec3(179.999991348578f, -23.73339277134586f, 179.999991348578f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 2;
    boxSize = vec3(1.0000005960464478f, 0.9999999403953552f, 1.0000005960464478f);
    boxPosition = vec3(-22.858861923217773f, 1.9999998807907104f, 18.720481872558594f);
    boxEulerAngles = vec3(179.999991348578f, -23.733394478893153f, 179.999991348578f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 2;
    boxSize = vec3(9.0f, 4.0f, 5.0f);
    boxPosition = vec3(-22.26280975341797f, 0.9999867081642151f, -0.05115675926208496f);
    boxEulerAngles = vec3(179.999991348578f, 0.0f, 179.999991348578f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(20.0f, 20.0f, 20.0f);
    boxPosition = vec3(0.0f, 9.0f, 60.0f);
    boxEulerAngles = vec3(0.0f, -0.0f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 2;
    boxSize = vec3(2.999969720840454f, 1.9999911785125732f, 3.999952793121338f);
    boxPosition = vec3(-17.134122848510742f, 0.0f, 2.518460988998413f);
    boxEulerAngles = vec3(0.0f, 60.457330645908655f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 2;
    boxSize = vec3(4.999832630157471f, 3.0f, 4.999993324279785f);
    boxPosition = vec3(18.351093292236328f, 0.5000176429748535f, 8.719722747802734f);
    boxEulerAngles = vec3(179.999991348578f, -14.096249423230805f, 179.999991348578f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(0.5f, 2.0f, 7.0f);
    boxPosition = vec3(-10.890523910522461f, 0.0f, -35.301090240478516f);
    boxEulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(4.0f, 3.0f, 2.0f);
    boxPosition = vec3(-49.953739166259766f, 0.5f, 5.168451309204102f);
    boxEulerAngles = vec3(0.0f, -69.99999967119774f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(4.0f, 7.0f, 1.999990463256836f);
    boxPosition = vec3(-44.0306396484375f, 2.5f, 20.40106964111328f);
    boxEulerAngles = vec3(0.0f, -45.95227305651143f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(4.999993324279785f, 6.999980926513672f, 4.999993324279785f);
    boxPosition = vec3(14.83809757232666f, 2.499999761581421f, -37.63517761230469f);
    boxEulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 2;
    boxSize = vec3(3.000000238418579f, 2.999999761581421f, 3.000000238418579f);
    boxPosition = vec3(17.829620361328125f, 2.9999845027923584f, -9.80679702758789f);
    boxEulerAngles = vec3(179.999991348578f, -71.10726895830518f, 179.999991348578f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 2;
    boxSize = vec3(1.0000003576278687f, 1.0f, 1.0000003576278687f);
    boxPosition = vec3(13.097940444946289f, 1.9999847412109375f, -6.686174392700195f);
    boxEulerAngles = vec3(179.999991348578f, -23.73339277134586f, 179.999991348578f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 2;
    boxSize = vec3(1.0000169277191162f, 0.9999843239784241f, 1.0000169277191162f);
    boxPosition = vec3(7.924259662628174f, 1.9999691247940063f, -6.570480823516846f);
    boxEulerAngles = vec3(0.0f, -84.12961200720312f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 2;
    boxSize = vec3(1.0000169277191162f, 0.9999842643737793f, 1.0000169277191162f);
    boxPosition = vec3(9.213461875915527f, 1.9999690055847168f, -6.489477634429932f);
    boxEulerAngles = vec3(0.0f, -84.12961200720312f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 2;
    boxSize = vec3(1.0000022649765015f, 0.9999843239784241f, 1.0000022649765015f);
    boxPosition = vec3(10.4910306930542f, 1.9999691247940063f, -5.678989887237549f);
    boxEulerAngles = vec3(0.0f, -84.12957785625727f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 2;
    boxSize = vec3(1.0000008344650269f, 0.9999999403953552f, 1.0000008344650269f);
    boxPosition = vec3(12.021892547607422f, 1.999984622001648f, -6.278343200683594f);
    boxEulerAngles = vec3(179.999991348578f, -23.73339277134586f, 179.999991348578f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    boxType = 1;
    boxSize = vec3(3.9999682903289795f, 2.9999806880950928f, 1.9999841451644897f);
    boxPosition = vec3(-23.76885414123535f, 0.4999694526195526f, 41.0047492980957f);
    boxEulerAngles = vec3(0.0f, 90.00000250447816f, 0.0f);
    MapSystemManager::Instance()->addMapBox(new MapBoxObject(boxType, boxSize, boxPosition, boxEulerAngles));
    
    MapSystemManager::Instance()->updateGrids();

    
    PBRShader* cubeShader = new PBRShader(0.5f, 0.5f);
    Node* testNode1 = new Node();
    testNode1->loadUnitCube();
    testNode1->geometries[0]->setShader(cubeShader);
    testNode1->scale = vec3(20.0f, 20.0f, 20.0f);
    testNode1->position = vec3(0.0f, 9.0f, 60.0f);
    testNode1->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    Engine::main->addNode(testNode1);
    Node* testNode2 = new Node();
    testNode2->loadUnitCube();
    testNode2->geometries[0]->setShader(cubeShader);
    testNode2->scale = vec3(20.0f, 1.0f, 40.0f);
    testNode2->position = vec3(0.0f, -1.5f, 30.0f);
    testNode2->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    Engine::main->addNode(testNode2);
    Node* testNode3 = new Node();
    testNode3->loadUnitCube();
    testNode3->geometries[0]->setShader(cubeShader);
    testNode3->scale = vec3(100.0f, 1.0f, 20.0f);
    testNode3->position = vec3(0.0f, -1.5f, 0.0f);
    testNode3->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    Engine::main->addNode(testNode3);
    Node* testNode4 = new Node();
    testNode4->loadUnitCube();
    testNode4->geometries[0]->setShader(cubeShader);
    testNode4->scale = vec3(20.0f, 1.0f, 40.0f);
    testNode4->position = vec3(0.0f, -1.5f, -30.0f);
    testNode4->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    Engine::main->addNode(testNode4);
    Node* testNode5 = new Node();
    testNode5->loadUnitCube();
    testNode5->geometries[0]->setShader(cubeShader);
    testNode5->scale = vec3(20.0f, 1.0f, 20.0f);
    testNode5->position = vec3(36.339744567871094f, -1.5f, 13.65999984741211f);
    testNode5->eulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    Engine::main->addNode(testNode5);
    Node* testNode6 = new Node();
    testNode6->loadUnitCube();
    testNode6->geometries[0]->setShader(cubeShader);
    testNode6->scale = vec3(20.0f, 1.0f, 20.0f);
    testNode6->position = vec3(26.200000762939453f, -1.5f, 27.0f);
    testNode6->eulerAngles = vec3(0.0f, 45.00000466733367f, 0.0f);
    Engine::main->addNode(testNode6);
    Node* testNode7 = new Node();
    testNode7->loadUnitCube();
    testNode7->geometries[0]->setShader(cubeShader);
    testNode7->scale = vec3(19.999998092651367f, 1.0f, 20.0f);
    testNode7->position = vec3(13.65999984741211f, -1.5f, 36.34000015258789f);
    testNode7->eulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    Engine::main->addNode(testNode7);
    Node* testNode8 = new Node();
    testNode8->loadUnitCube();
    testNode8->geometries[0]->setShader(cubeShader);
    testNode8->scale = vec3(20.0f, 1.0f, 20.0f);
    testNode8->position = vec3(20.0f, -1.5f, 20.0f);
    testNode8->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    Engine::main->addNode(testNode8);
    Node* testNode9 = new Node();
    testNode9->loadUnitCube();
    testNode9->geometries[0]->setShader(cubeShader);
    testNode9->scale = vec3(19.999998092651367f, 1.0f, 20.0f);
    testNode9->position = vec3(-13.600000381469727f, -1.5f, -36.33000183105469f);
    testNode9->eulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    Engine::main->addNode(testNode9);
    Node* testNode10 = new Node();
    testNode10->loadUnitCube();
    testNode10->geometries[0]->setShader(cubeShader);
    testNode10->scale = vec3(20.0f, 1.0f, 20.0f);
    testNode10->position = vec3(-36.34000015258789f, -1.5f, -13.600000381469727f);
    testNode10->eulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    Engine::main->addNode(testNode10);
    Node* testNode11 = new Node();
    testNode11->loadUnitCube();
    testNode11->geometries[0]->setShader(cubeShader);
    testNode11->scale = vec3(20.0f, 1.0f, 20.0f);
    testNode11->position = vec3(-26.95877456665039f, -1.5f, -26.158771514892578f);
    testNode11->eulerAngles = vec3(0.0f, 45.00000466733367f, 0.0f);
    Engine::main->addNode(testNode11);
    Node* testNode12 = new Node();
    testNode12->loadUnitCube();
    testNode12->geometries[0]->setShader(cubeShader);
    testNode12->scale = vec3(20.0f, 1.0f, 20.0f);
    testNode12->position = vec3(-20.0f, -1.5f, -20.0f);
    testNode12->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    Engine::main->addNode(testNode12);
    Node* testNode13 = new Node();
    testNode13->loadUnitCube();
    testNode13->geometries[0]->setShader(cubeShader);
    testNode13->scale = vec3(20.0f, 1.0f, 20.0f);
    testNode13->position = vec3(20.0f, -1.5f, -20.0f);
    testNode13->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    Engine::main->addNode(testNode13);
    Node* testNode14 = new Node();
    testNode14->loadUnitCube();
    testNode14->geometries[0]->setShader(cubeShader);
    testNode14->scale = vec3(20.0f, 1.0f, 20.0f);
    testNode14->position = vec3(-20.0f, -1.5f, 20.0f);
    testNode14->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    Engine::main->addNode(testNode14);
    Node* testNode15 = new Node();
    testNode15->loadUnitCube();
    testNode15->geometries[0]->setShader(cubeShader);
    testNode15->scale = vec3(19.999998092651367f, 1.0f, 20.0f);
    testNode15->position = vec3(-13.731363296508789f, -1.5f, 36.58491516113281f);
    testNode15->eulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    Engine::main->addNode(testNode15);
    Node* testNode16 = new Node();
    testNode16->loadUnitCube();
    testNode16->geometries[0]->setShader(cubeShader);
    testNode16->scale = vec3(19.999998092651367f, 1.0f, 20.0f);
    testNode16->position = vec3(-36.34000015258789f, -1.5f, 13.601505279541016f);
    testNode16->eulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    Engine::main->addNode(testNode16);
    Node* testNode17 = new Node();
    testNode17->loadUnitCube();
    testNode17->geometries[0]->setShader(cubeShader);
    testNode17->scale = vec3(20.0f, 1.0f, 20.0f);
    testNode17->position = vec3(-26.481189727783203f, -1.5f, 26.653076171875f);
    testNode17->eulerAngles = vec3(0.0f, 45.00000466733367f, 0.0f);
    Engine::main->addNode(testNode17);
    Node* testNode18 = new Node();
    testNode18->loadUnitCube();
    testNode18->geometries[0]->setShader(cubeShader);
    testNode18->scale = vec3(19.999998092651367f, 1.0f, 20.0f);
    testNode18->position = vec3(13.596307754516602f, -1.5f, -36.33232116699219f);
    testNode18->eulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    Engine::main->addNode(testNode18);
    Node* testNode19 = new Node();
    testNode19->loadUnitCube();
    testNode19->geometries[0]->setShader(cubeShader);
    testNode19->scale = vec3(20.0f, 1.0f, 20.0f);
    testNode19->position = vec3(26.81570053100586f, -1.5f, -26.241455078125f);
    testNode19->eulerAngles = vec3(0.0f, 45.00000466733367f, 0.0f);
    Engine::main->addNode(testNode19);
    Node* testNode20 = new Node();
    testNode20->loadUnitCube();
    testNode20->geometries[0]->setShader(cubeShader);
    testNode20->scale = vec3(19.999998092651367f, 1.0f, 20.0f);
    testNode20->position = vec3(36.2993278503418f, -1.5f, -13.646175384521484f);
    testNode20->eulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    Engine::main->addNode(testNode20);
    Node* testNode21 = new Node();
    testNode21->loadUnitCube();
    testNode21->geometries[0]->setShader(cubeShader);
    testNode21->scale = vec3(20.0f, 20.0f, 20.0f);
    testNode21->position = vec3(0.0f, 9.0f, -60.0f);
    testNode21->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    Engine::main->addNode(testNode21);
    Node* testNode22 = new Node();
    testNode22->loadUnitCube();
    testNode22->geometries[0]->setShader(cubeShader);
    testNode22->scale = vec3(5.0f, 30.0f, 20.0f);
    testNode22->position = vec3(-19.679931640625f, 13.0f, 47.426387786865234f);
    testNode22->eulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    Engine::main->addNode(testNode22);
    Node* testNode23 = new Node();
    testNode23->loadUnitCube();
    testNode23->geometries[0]->setShader(cubeShader);
    testNode23->scale = vec3(5.0f, 30.0f, 20.0f);
    testNode23->position = vec3(-35.30475616455078f, 13.0f, 35.362510681152344f);
    testNode23->eulerAngles = vec3(0.0f, 44.999994422049916f, 0.0f);
    Engine::main->addNode(testNode23);
    Node* testNode24 = new Node();
    testNode24->loadUnitCube();
    testNode24->geometries[0]->setShader(cubeShader);
    testNode24->scale = vec3(20.0f, 30.0f, 5.0f);
    testNode24->position = vec3(-47.292022705078125f, 13.0f, 19.538402557373047f);
    testNode24->eulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    Engine::main->addNode(testNode24);
    Node* testNode25 = new Node();
    testNode25->loadUnitCube();
    testNode25->geometries[0]->setShader(cubeShader);
    testNode25->scale = vec3(19.9999942779541f, 30.0f, 4.999998569488525f);
    testNode25->position = vec3(-52.50025177001953f, 13.0f, -0.058162689208984375f);
    testNode25->eulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    Engine::main->addNode(testNode25);
    Node* testNode26 = new Node();
    testNode26->loadUnitCube();
    testNode26->geometries[0]->setShader(cubeShader);
    testNode26->scale = vec3(20.0f, 30.0f, 5.0f);
    testNode26->position = vec3(-47.196224212646484f, 13.0f, -19.518991470336914f);
    testNode26->eulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    Engine::main->addNode(testNode26);
    Node* testNode27 = new Node();
    testNode27->loadUnitCube();
    testNode27->geometries[0]->setShader(cubeShader);
    testNode27->scale = vec3(5.0f, 30.0f, 20.0f);
    testNode27->position = vec3(-35.77626037597656f, 13.0f, -34.86589431762695f);
    testNode27->eulerAngles = vec3(0.0f, -44.999994422049916f, 0.0f);
    Engine::main->addNode(testNode27);
    Node* testNode28 = new Node();
    testNode28->loadUnitCube();
    testNode28->geometries[0]->setShader(cubeShader);
    testNode28->scale = vec3(5.0f, 30.0f, 20.0f);
    testNode28->position = vec3(-19.81863021850586f, 13.0f, -47.04525375366211f);
    testNode28->eulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    Engine::main->addNode(testNode28);
    Node* testNode29 = new Node();
    testNode29->loadUnitCube();
    testNode29->geometries[0]->setShader(cubeShader);
    testNode29->scale = vec3(5.0f, 30.0f, 5.0f);
    testNode29->position = vec3(14.256914138793945f, 14.0f, 40.71234130859375f);
    testNode29->eulerAngles = vec3(0.0f, -60.000001669652114f, 0.0f);
    Engine::main->addNode(testNode29);
    Node* testNode30 = new Node();
    testNode30->loadUnitCube();
    testNode30->geometries[0]->setShader(cubeShader);
    testNode30->scale = vec3(29.999935150146484f, 2.999999523162842f, 16.999998092651367f);
    testNode30->position = vec3(-36.28617477416992f, -1.132124423980713f, -18.673717498779297f);
    testNode30->eulerAngles = vec3(9.99999970909292f, 60.00000849984128f, -1.707547699614187e-06f);
    Engine::main->addNode(testNode30);
    Node* testNode31 = new Node();
    testNode31->loadUnitCube();
    testNode31->geometries[0]->setShader(cubeShader);
    testNode31->scale = vec3(5.0f, 30.0f, 5.0f);
    testNode31->position = vec3(27.738876342773438f, 14.0f, 30.06119155883789f);
    testNode31->eulerAngles = vec3(0.0f, -44.999994422049916f, 0.0f);
    Engine::main->addNode(testNode31);
    Node* testNode32 = new Node();
    testNode32->loadUnitCube();
    testNode32->geometries[0]->setShader(cubeShader);
    testNode32->scale = vec3(5.0f, 7.0f, 5.0f);
    testNode32->position = vec3(27.201324462890625f, 2.5f, -26.600440979003906f);
    testNode32->eulerAngles = vec3(0.0f, 44.999994422049916f, 0.0f);
    Engine::main->addNode(testNode32);
    Node* testNode33 = new Node();
    testNode33->loadUnitCube();
    testNode33->geometries[0]->setShader(cubeShader);
    testNode33->scale = vec3(9.999994277954102f, 2.5f, 14.99999713897705f);
    testNode33->position = vec3(-19.002153396606445f, 0.24999995529651642f, 24.259979248046875f);
    testNode33->eulerAngles = vec3(0.0f, 59.99999483946294f, 0.0f);
    Engine::main->addNode(testNode33);
    Node* testNode34 = new Node();
    testNode34->loadUnitCube();
    testNode34->geometries[0]->setShader(cubeShader);
    testNode34->scale = vec3(4.999887943267822f, 4.999917030334473f, 22.999780654907227f);
    testNode34->position = vec3(34.57914733886719f, 2.5202579498291016f, -17.966392517089844f);
    testNode34->eulerAngles = vec3(13.46300038716412f, 38.7630003512636f, 0.0f);
    Engine::main->addNode(testNode34);
    Node* testNode35 = new Node();
    testNode35->loadUnitCube();
    testNode35->geometries[0]->setShader(cubeShader);
    testNode35->scale = vec3(9.999835968017578f, 2.499964952468872f, 14.999848365783691f);
    testNode35->position = vec3(12.881000518798828f, 0.24999994039535522f, -10.011907577514648f);
    testNode35->eulerAngles = vec3(0.0f, -69.99999967119774f, 0.0f);
    Engine::main->addNode(testNode35);
    Node* testNode36 = new Node();
    testNode36->loadUnitCube();
    testNode36->geometries[0]->setShader(cubeShader);
    testNode36->scale = vec3(4.999978542327881f, 3.000000238418579f, 17.00000762939453f);
    testNode36->position = vec3(-5.298661231994629f, -1.336275339126587f, 31.8536376953125f);
    testNode36->eulerAngles = vec3(8.999993420258647f, 60.00000849984128f, -5.122643913064559e-06f);
    Engine::main->addNode(testNode36);
    Node* testNode37 = new Node();
    testNode37->loadUnitCube();
    testNode37->geometries[0]->setShader(cubeShader);
    testNode37->scale = vec3(0.5f, 2.0f, 5.0f);
    testNode37->position = vec3(10.21187973022461f, 0.0f, 21.193662643432617f);
    testNode37->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    Engine::main->addNode(testNode37);
    Node* testNode38 = new Node();
    testNode38->loadUnitCube();
    testNode38->geometries[0]->setShader(cubeShader);
    testNode38->scale = vec3(0.4999998211860657f, 1.0f, 9.99999713897705f);
    testNode38->position = vec3(25.113908767700195f, -0.5f, 11.59774398803711f);
    testNode38->eulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    Engine::main->addNode(testNode38);
    Node* testNode39 = new Node();
    testNode39->loadUnitCube();
    testNode39->geometries[0]->setShader(cubeShader);
    testNode39->scale = vec3(0.5f, 1.0f, 10.0f);
    testNode39->position = vec3(4.626926422119141f, -0.5f, 7.29351806640625f);
    testNode39->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    Engine::main->addNode(testNode39);
    Node* testNode40 = new Node();
    testNode40->loadUnitCube();
    testNode40->geometries[0]->setShader(cubeShader);
    testNode40->scale = vec3(5.000000953674316f, 3.0f, 17.0f);
    testNode40->position = vec3(5.108200550079346f, -1.3108752965927124f, -21.101150512695312f);
    testNode40->eulerAngles = vec3(-9.000000250447817f, 19.99999771063855f, 5.6785429905125e-07f);
    Engine::main->addNode(testNode40);
    Node* testNode41 = new Node();
    testNode41->loadUnitCube();
    testNode41->geometries[0]->setShader(cubeShader);
    testNode41->scale = vec3(0.5f, 2.0f, 10.0f);
    testNode41->position = vec3(-6.175685882568359f, 0.0f, -4.580935478210449f);
    testNode41->eulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    Engine::main->addNode(testNode41);
    Node* testNode42 = new Node();
    testNode42->loadUnitCube();
    testNode42->geometries[0]->setShader(cubeShader);
    testNode42->scale = vec3(0.5f, 2.0f, 7.0f);
    testNode42->position = vec3(-10.48333740234375f, 0.0f, 9.90719985961914f);
    testNode42->eulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    Engine::main->addNode(testNode42);
    Node* testNode43 = new Node();
    testNode43->loadUnitCube();
    testNode43->geometries[0]->setShader(cubeShader);
    testNode43->scale = vec3(0.4999997913837433f, 1.0f, 3.999999761581421f);
    testNode43->position = vec3(2.3769264221191406f, -0.5f, 6.538968086242676f);
    testNode43->eulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    Engine::main->addNode(testNode43);
    Node* testNode44 = new Node();
    testNode44->loadUnitCube();
    testNode44->geometries[0]->setShader(cubeShader);
    testNode44->scale = vec3(0.5f, 2.0f, 5.0f);
    testNode44->position = vec3(-9.59457778930664f, 0.0f, -1.830935001373291f);
    testNode44->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    Engine::main->addNode(testNode44);
    Node* testNode45 = new Node();
    testNode45->loadUnitCube();
    testNode45->geometries[0]->setShader(cubeShader);
    testNode45->scale = vec3(4.9999680519104f, 0.9999958872795105f, 6.999967098236084f);
    testNode45->position = vec3(-12.002592086791992f, -0.4999999701976776f, -18.14734649658203f);
    testNode45->eulerAngles = vec3(0.0f, 33.53639957949186f, 0.0f);
    Engine::main->addNode(testNode45);
    Node* testNode46 = new Node();
    testNode46->loadUnitCube();
    testNode46->geometries[0]->setShader(cubeShader);
    testNode46->scale = vec3(2.9999992847442627f, 2.0f, 3.9999990463256836f);
    testNode46->position = vec3(-7.776100158691406f, 0.0f, -15.409856796264648f);
    testNode46->eulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    Engine::main->addNode(testNode46);
    Node* testNode47 = new Node();
    testNode47->loadUnitCube();
    testNode47->geometries[0]->setShader(cubeShader);
    testNode47->scale = vec3(4.999841690063477f, 4.0f, 5.0f);
    testNode47->position = vec3(40.72988510131836f, 0.9999867081642151f, 2.3642375469207764f);
    testNode47->eulerAngles = vec3(179.999991348578f, 20.135100559968695f, 179.999991348578f);
    Engine::main->addNode(testNode47);
    Node* testNode48 = new Node();
    testNode48->loadUnitCube();
    testNode48->geometries[0]->setShader(cubeShader);
    testNode48->scale = vec3(4.999831199645996f, 3.0f, 4.9999918937683105f);
    testNode48->position = vec3(39.35308837890625f, 0.5000176429748535f, 7.0984416007995605f);
    testNode48->eulerAngles = vec3(179.999991348578f, -14.096251130778096f, 179.999991348578f);
    Engine::main->addNode(testNode48);
    Node* testNode49 = new Node();
    testNode49->loadUnitCube();
    testNode49->geometries[0]->setShader(cubeShader);
    testNode49->scale = vec3(4.999912738800049f, 4.0f, 5.00007438659668f);
    testNode49->position = vec3(39.572853088378906f, 0.9999866485595703f, 11.962966918945312f);
    testNode49->eulerAngles = vec3(179.999991348578f, -71.10730310925103f, 179.999991348578f);
    Engine::main->addNode(testNode49);
    Node* testNode50 = new Node();
    testNode50->loadUnitCube();
    testNode50->geometries[0]->setShader(cubeShader);
    testNode50->scale = vec3(3.0f, 2.999999761581421f, 3.0f);
    testNode50->position = vec3(-13.633177757263184f, 2.999999761581421f, 23.612285614013672f);
    testNode50->eulerAngles = vec3(179.999991348578f, -71.10728261868353f, 179.999991348578f);
    Engine::main->addNode(testNode50);
    Node* testNode51 = new Node();
    testNode51->loadUnitCube();
    testNode51->geometries[0]->setShader(cubeShader);
    testNode51->scale = vec3(1.0000003576278687f, 1.0f, 1.0000003576278687f);
    testNode51->position = vec3(-21.799108505249023f, 2.0f, 18.328943252563477f);
    testNode51->eulerAngles = vec3(179.999991348578f, -23.733391063798567f, 179.999991348578f);
    Engine::main->addNode(testNode51);
    Node* testNode52 = new Node();
    testNode52->loadUnitCube();
    testNode52->geometries[0]->setShader(cubeShader);
    testNode52->scale = vec3(1.0000003576278687f, 1.0f, 1.0000003576278687f);
    testNode52->position = vec3(-21.782814025878906f, 2.0f, 18.312650680541992f);
    testNode52->eulerAngles = vec3(179.999991348578f, -23.73339277134586f, 179.999991348578f);
    Engine::main->addNode(testNode52);
    Node* testNode53 = new Node();
    testNode53->loadUnitCube();
    testNode53->geometries[0]->setShader(cubeShader);
    testNode53->scale = vec3(1.0000003576278687f, 1.0f, 1.0000003576278687f);
    testNode53->position = vec3(-21.2570743560791f, 2.0f, 19.338041305541992f);
    testNode53->eulerAngles = vec3(179.999991348578f, -23.733394478893153f, 179.999991348578f);
    Engine::main->addNode(testNode53);
    Node* testNode54 = new Node();
    testNode54->loadUnitCube();
    testNode54->geometries[0]->setShader(cubeShader);
    testNode54->scale = vec3(1.0000003576278687f, 0.9999999403953552f, 1.0000003576278687f);
    testNode54->position = vec3(-19.967870712280273f, 1.9999998807907104f, 19.419044494628906f);
    testNode54->eulerAngles = vec3(179.999991348578f, -23.73339277134586f, 179.999991348578f);
    Engine::main->addNode(testNode54);
    Node* testNode55 = new Node();
    testNode55->loadUnitCube();
    testNode55->geometries[0]->setShader(cubeShader);
    testNode55->scale = vec3(1.0000003576278687f, 1.0f, 1.0000003576278687f);
    testNode55->position = vec3(-18.6903018951416f, 2.0f, 20.22953224182129f);
    testNode55->eulerAngles = vec3(179.999991348578f, -23.73339277134586f, 179.999991348578f);
    Engine::main->addNode(testNode55);
    Node* testNode56 = new Node();
    testNode56->loadUnitCube();
    testNode56->geometries[0]->setShader(cubeShader);
    testNode56->scale = vec3(1.0000005960464478f, 0.9999999403953552f, 1.0000005960464478f);
    testNode56->position = vec3(-22.858861923217773f, 1.9999998807907104f, 18.720481872558594f);
    testNode56->eulerAngles = vec3(179.999991348578f, -23.733394478893153f, 179.999991348578f);
    Engine::main->addNode(testNode56);
    Node* testNode57 = new Node();
    testNode57->loadUnitCube();
    testNode57->geometries[0]->setShader(cubeShader);
    testNode57->scale = vec3(9.0f, 4.0f, 5.0f);
    testNode57->position = vec3(-22.26280975341797f, 0.9999867081642151f, -0.05115675926208496f);
    testNode57->eulerAngles = vec3(179.999991348578f, 0.0f, 179.999991348578f);
    Engine::main->addNode(testNode57);
    Node* testNode58 = new Node();
    testNode58->loadUnitCube();
    testNode58->geometries[0]->setShader(cubeShader);
    testNode58->scale = vec3(20.0f, 20.0f, 20.0f);
    testNode58->position = vec3(0.0f, 9.0f, 60.0f);
    testNode58->eulerAngles = vec3(0.0f, -0.0f, 0.0f);
    Engine::main->addNode(testNode58);
    Node* testNode59 = new Node();
    testNode59->loadUnitCube();
    testNode59->geometries[0]->setShader(cubeShader);
    testNode59->scale = vec3(2.999969720840454f, 1.9999911785125732f, 3.999952793121338f);
    testNode59->position = vec3(-17.134122848510742f, 0.0f, 2.518460988998413f);
    testNode59->eulerAngles = vec3(0.0f, 60.457330645908655f, 0.0f);
    Engine::main->addNode(testNode59);
    Node* testNode60 = new Node();
    testNode60->loadUnitCube();
    testNode60->geometries[0]->setShader(cubeShader);
    testNode60->scale = vec3(4.999832630157471f, 3.0f, 4.999993324279785f);
    testNode60->position = vec3(18.351093292236328f, 0.5000176429748535f, 8.719722747802734f);
    testNode60->eulerAngles = vec3(179.999991348578f, -14.096249423230805f, 179.999991348578f);
    Engine::main->addNode(testNode60);
    Node* testNode61 = new Node();
    testNode61->loadUnitCube();
    testNode61->geometries[0]->setShader(cubeShader);
    testNode61->scale = vec3(0.5f, 2.0f, 7.0f);
    testNode61->position = vec3(-10.890523910522461f, 0.0f, -35.301090240478516f);
    testNode61->eulerAngles = vec3(-0.0f, -90.00000250447816f, 0.0f);
    Engine::main->addNode(testNode61);
    Node* testNode62 = new Node();
    testNode62->loadUnitCube();
    testNode62->geometries[0]->setShader(cubeShader);
    testNode62->scale = vec3(4.0f, 3.0f, 2.0f);
    testNode62->position = vec3(-49.953739166259766f, 0.5f, 5.168451309204102f);
    testNode62->eulerAngles = vec3(0.0f, -69.99999967119774f, 0.0f);
    Engine::main->addNode(testNode62);
    Node* testNode63 = new Node();
    testNode63->loadUnitCube();
    testNode63->geometries[0]->setShader(cubeShader);
    testNode63->scale = vec3(4.0f, 7.0f, 1.999990463256836f);
    testNode63->position = vec3(-44.0306396484375f, 2.5f, 20.40106964111328f);
    testNode63->eulerAngles = vec3(0.0f, -45.95227305651143f, 0.0f);
    Engine::main->addNode(testNode63);
    Node* testNode64 = new Node();
    testNode64->loadUnitCube();
    testNode64->geometries[0]->setShader(cubeShader);
    testNode64->scale = vec3(4.999993324279785f, 6.999980926513672f, 4.999993324279785f);
    testNode64->position = vec3(14.83809757232666f, 2.499999761581421f, -37.63517761230469f);
    testNode64->eulerAngles = vec3(0.0f, 60.000001669652114f, 0.0f);
    Engine::main->addNode(testNode64);
    Node* testNode65 = new Node();
    testNode65->loadUnitCube();
    testNode65->geometries[0]->setShader(cubeShader);
    testNode65->scale = vec3(3.000000238418579f, 2.999999761581421f, 3.000000238418579f);
    testNode65->position = vec3(17.829620361328125f, 2.9999845027923584f, -9.80679702758789f);
    testNode65->eulerAngles = vec3(179.999991348578f, -71.10726895830518f, 179.999991348578f);
    Engine::main->addNode(testNode65);
    Node* testNode66 = new Node();
    testNode66->loadUnitCube();
    testNode66->geometries[0]->setShader(cubeShader);
    testNode66->scale = vec3(1.0000003576278687f, 1.0f, 1.0000003576278687f);
    testNode66->position = vec3(13.097940444946289f, 1.9999847412109375f, -6.686174392700195f);
    testNode66->eulerAngles = vec3(179.999991348578f, -23.73339277134586f, 179.999991348578f);
    Engine::main->addNode(testNode66);
    Node* testNode67 = new Node();
    testNode67->loadUnitCube();
    testNode67->geometries[0]->setShader(cubeShader);
    testNode67->scale = vec3(1.0000169277191162f, 0.9999843239784241f, 1.0000169277191162f);
    testNode67->position = vec3(7.924259662628174f, 1.9999691247940063f, -6.570480823516846f);
    testNode67->eulerAngles = vec3(0.0f, -84.12961200720312f, 0.0f);
    Engine::main->addNode(testNode67);
    Node* testNode68 = new Node();
    testNode68->loadUnitCube();
    testNode68->geometries[0]->setShader(cubeShader);
    testNode68->scale = vec3(1.0000169277191162f, 0.9999842643737793f, 1.0000169277191162f);
    testNode68->position = vec3(9.213461875915527f, 1.9999690055847168f, -6.489477634429932f);
    testNode68->eulerAngles = vec3(0.0f, -84.12961200720312f, 0.0f);
    Engine::main->addNode(testNode68);
    Node* testNode69 = new Node();
    testNode69->loadUnitCube();
    testNode69->geometries[0]->setShader(cubeShader);
    testNode69->scale = vec3(1.0000022649765015f, 0.9999843239784241f, 1.0000022649765015f);
    testNode69->position = vec3(10.4910306930542f, 1.9999691247940063f, -5.678989887237549f);
    testNode69->eulerAngles = vec3(0.0f, -84.12957785625727f, 0.0f);
    Engine::main->addNode(testNode69);
    Node* testNode70 = new Node();
    testNode70->loadUnitCube();
    testNode70->geometries[0]->setShader(cubeShader);
    testNode70->scale = vec3(1.0000008344650269f, 0.9999999403953552f, 1.0000008344650269f);
    testNode70->position = vec3(12.021892547607422f, 1.999984622001648f, -6.278343200683594f);
    testNode70->eulerAngles = vec3(179.999991348578f, -23.73339277134586f, 179.999991348578f);
    Engine::main->addNode(testNode70);
    Node* testNode71 = new Node();
    testNode71->loadUnitCube();
    testNode71->geometries[0]->setShader(cubeShader);
    testNode71->scale = vec3(3.9999682903289795f, 2.9999806880950928f, 1.9999841451644897f);
    testNode71->position = vec3(-23.76885414123535f, 0.4999694526195526f, 41.0047492980957f);
    testNode71->eulerAngles = vec3(0.0f, 90.00000250447816f, 0.0f);
    Engine::main->addNode(testNode71);
}


void importMapModel() {
    Node* newMap = new Node();
    newMap->loadModelFile("/Resources/Game/Map/MergedMapBase.dae");
    newMap->position.z -= 55;
//    newMap->scale = vec3(5);
    newMap->position.y -= 101;
    
    
    PBRShader* wallShader = new PBRShader(0.1f, 0.2f);
    wallShader->setDiffuseMap(new Texture("/Resources/Game/Map/T_Wall_01_Albedo.png", 2, true));
    wallShader->setNormalMap(new Texture("/Resources/Game/Map/T_Wall_01_Normal.png", 1, true));
    wallShader->alphaCutThreshold = 0.0f;
    newMap->geometries[0]->setDoubleSided();
    newMap->geometries[0]->setShader(wallShader);
    PBRShader* wallShader2 = new PBRShader(0.1f, 0.2f);
    wallShader2->setDiffuseMap(new Texture("/Resources/Game/Map/T_Wall_03_Albedo.png", 2, true));
    wallShader2->setNormalMap(new Texture("/Resources/Game/Map/T_Wall_03_Normal.png", 1, true));
    wallShader2->alphaCutThreshold = 0.0f;
    newMap->geometries[1]->setDoubleSided();
    newMap->geometries[1]->setShader(wallShader2);
    PBRShader* wallShader3 = new PBRShader(0.1f, 0.2f);
    wallShader3->setDiffuseMap(new Texture("/Resources/Game/Map/T_Bricks_01_Albedo.png", 2, true));
    wallShader3->setNormalMap(new Texture("/Resources/Game/Map/T_Bricks_01_Normal.png", 1, true));
    wallShader3->alphaCutThreshold = 0.0f;
    newMap->geometries[2]->setDoubleSided();
    newMap->geometries[2]->setShader(wallShader3);
    PBRShader* wallShader4 = new PBRShader(0.1f, 0.2f);
    wallShader4->setDiffuseMap(new Texture("/Resources/Game/Map/T_Floor_01_Albedo.png", 2, true));
    wallShader4->setNormalMap(new Texture("/Resources/Game/Map/T_Floor_01_Normal.png", 1, true));
    wallShader4->alphaCutThreshold = 0.0f;
    newMap->geometries[3]->setDoubleSided();
    newMap->geometries[3]->setShader(wallShader4);
    PBRShader* wallShader5 = new PBRShader(0.1f, 0.2f);
    wallShader5->setDiffuseMap(new Texture("/Resources/Game/Map/T_Floor_Bricks_01_Albedo.png", 2, true));
    wallShader5->setNormalMap(new Texture("/Resources/Game/Map/T_Floor_Bricks_01_Normal.png", 1, true));
    wallShader5->alphaCutThreshold = 0.0f;
    newMap->geometries[4]->setDoubleSided();
    newMap->geometries[4]->setShader(wallShader5);
    PBRShader* wallShader6 = new PBRShader(0.1f, 0.2f);
    wallShader6->setDiffuseMap(new Texture("/Resources/Game/Map/T_Trim_01_Albedo.png", 2, true));
    wallShader6->setNormalMap(new Texture("/Resources/Game/Map/T_Trim_01_Normal.png", 1, true));
    wallShader6->alphaCutThreshold = 0.0f;
    newMap->geometries[5]->setDoubleSided();
    newMap->geometries[5]->setShader(wallShader6);
    PBRShader* wallShader7 = new PBRShader(0.1f, 0.2f);
    wallShader7->setDiffuseMap(new Texture("/Resources/Game/Map/T_Battlement_01_Albedo.png", 2, true));
    wallShader7->setNormalMap(new Texture("/Resources/Game/Map/T_Battlement_01_Normal.png", 1, true));
    wallShader7->alphaCutThreshold = 0.0f;
    newMap->geometries[6]->setDoubleSided();
    newMap->geometries[6]->setShader(wallShader7);
    PBRShader* wallShader8 = new PBRShader(0.1f, 0.2f);
    wallShader8->setDiffuseMap(new Texture("/Resources/Game/Map/T_Metal_Surface_01_Albedo.png", 2, true));
    wallShader8->setNormalMap(new Texture("/Resources/Game/Map/T_Metal_Surface_01_Normal.png", 1, true));
    wallShader8->alphaCutThreshold = 0.0f;
    newMap->geometries[7]->setDoubleSided();
    newMap->geometries[7]->setShader(wallShader8);
    PBRShader* wallShader9 = new PBRShader(0.1f, 0.2f);
    wallShader9->setDiffuseMap(new Texture("/Resources/Game/Map/New Terrain Basemap Diffuse.png", 2, true));
    wallShader9->setNormalMap(new Texture("/Resources/Game/Map/New Terrain Basemap Normal.png", 1, true));
    wallShader9->alphaCutThreshold = 0.0f;
    newMap->geometries[8]->setDoubleSided();
    newMap->geometries[8]->setShader(wallShader9);
    PBRShader* wallShadera = new PBRShader(0.1f, 0.2f);
    wallShadera->setDiffuseMap(new Texture("/Resources/Game/Map/T_Column_01_Albedo.png", 2, true));
    wallShadera->setNormalMap(new Texture("/Resources/Game/Map/T_Column_01_Normal.png", 1, true));
    wallShadera->alphaCutThreshold = 0.0f;
    newMap->geometries[9]->setDoubleSided();
    newMap->geometries[9]->setShader(wallShadera);
    
    for (int n = 11; n < newMap->geometries.size(); n++) {
        newMap->geometries[n]->setShader(new PBRShader(0.5, 0.5));
    }
    Engine::main->addNode(newMap);
}

} // namespace ImportMapHelper
