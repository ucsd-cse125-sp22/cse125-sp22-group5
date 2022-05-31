//
//  Color.hpp
//  KGLEngine
//
//  Created by Jackie Li on 4/26/22.
//

#ifndef Constant_hpp
#define Constant_hpp

namespace Color{
	const glm::vec4 ButtonBackground = glm::vec4(0.345098,0.7607843,1.0,1.0);
	const glm::vec4 ButtonBackgroundOff = glm::vec4(0.2,0.4,0.6,1.0);
	const glm::vec4 Hp = glm::vec4(0.45,0.15,0.15,1.0);
	const glm::vec4 Mp = glm::vec4(0.2,0.2,0.7,1.0);
	const glm::vec4 textColor = glm::vec4(0.76,0.67,0.5,1.0);
	const glm::vec4 LogotextColor = glm::vec4(0.9, 0.79, 0.33, 1.0);
	const glm::vec4 loadingBarColor = glm::vec4(0.3, 0.4, 0.9, 1.0);
};

namespace UISizes{

	const glm::vec2 cursorSize = glm::vec2(0.032);

	// General ============
	const glm::vec2 avatarSize = glm::vec2(0.140, 0.140);
	const glm::vec2 avatarIconSize = glm::vec2(0.124);
	const glm::vec2 avatarIconScale = glm::vec2(0.4);

	// Main ============
	const glm::vec2 leftBackSize = glm::vec2(0.4,0.2);
	const glm::vec2 mainBackgroundSize = glm::vec2(0.782,0.122);
	const glm::vec2 mainHpBarSize = glm::vec2(0.754,0.054);
	const glm::vec2 mainHpFadeBarSize = glm::vec2(0.754, 0.054);
	const glm::vec2 mainMpBarSize = glm::vec2(0.666,0.053);
	const glm::vec2 mainMpFadeBarSize = glm::vec2(0.661, 0.051);
	const glm::vec2 mainAvatarBackRedSize = glm::vec2(0.99,0.267);
	const glm::vec2 mainAvatarBackBlueSize = glm::vec2(0.925, 0.227);
	const glm::vec2 mainAvatarRedTopSize = glm::vec2(0.107,0.165);
	const glm::vec2 mainAvatarBlueTopSize = glm::vec2(0.107, 0.165);

	// Party ==============
	//const glm::vec2 partyBackgroundSize = glm::vec2(0.628, 0.122);
	const glm::vec2 partyBackgroundSize = glm::vec2(0.628, 0.122);
	const glm::vec2 partyHpBarSize = glm::vec2(0.605, 0.054);
	const glm::vec2 partyHpFadeBarSize = glm::vec2(0.605, 0.054);
	const glm::vec2 partyMpBarSize = glm::vec2(0.535, 0.050);
	const glm::vec2 partyMpFadeBarSize = glm::vec2(0.531, 0.050);
	const glm::vec2 partyAvatarBackSize = glm::vec2(0.17, 0.17);
	const glm::vec2 partyAvatarRedTopSize = glm::vec2(0.107, 0.165);
	const glm::vec2 partyAvatarBlueTopSize = glm::vec2(0.107, 0.165);

	// Magic ==============
	const glm::vec2 magicBackSize = glm::vec2(0.431,0.431);
	const glm::vec2 magicButtonBackSize = glm::vec2(0.206, 0.206);
	const glm::vec2 magicIconSize = glm::vec2(0.195);
	const glm::vec2 magicIconSmallScale = glm::vec2(0.6);
	const glm::vec2 magicIconLargeScale = glm::vec2(0.8);
	const glm::vec2 magicSelect = glm::vec2(0.316);
	const glm::vec2 magicCooldownSize = glm::vec2(0.194);
	const glm::vec2 magicPorgessSize = glm::vec2(0.197);

	// Enermy ==============
	const glm::vec2 enBackgroundSize = glm::vec2(0.626, 0.077);
	const glm::vec2 enHpBarSize = glm::vec2(0.605, 0.054);
	const glm::vec2 enHpFadeBarSize = glm::vec2(0.605, 0.054);
	const glm::vec2 enAvatarBackSize = glm::vec2(0.155, 0.151);
	const glm::vec2 enAvatarRedTopSize = glm::vec2(0.117, 0.152);
	const glm::vec2 enAvatarBlueTopSize = glm::vec2(0.117, 0.152);

	// tutorial ===============
	const glm::vec2 listHeadBackSize = glm::vec2(0.232,0.078);

	// notification ===============
	const glm::vec2 viewBackSize = glm::vec2(0.569,0.101);
	const glm::vec2 deathBackSize = glm::vec2(1.419,0.101);

	// logo =================
	const glm::vec2 logoLightSize = glm::vec2(1.018,0.585);
	const glm::vec2 logoBackSize = glm::vec2(0.864, 0.324);

	// button ===============
	const glm::vec2 buttonSize = glm::vec2(0.276,0.094);

	// windows ==============
	const glm::vec2 netWinBackSize = glm::vec2(0.852,0.078);

	// end ================
	const glm::vec2 endLogoSize = glm::vec2(0.539,0.238);
	
};

#endif
