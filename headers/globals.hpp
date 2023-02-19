#pragma once

namespace globals
{
	enum EGodMode
	{
		Partial,
		Full
	};

	inline bool godmode = true;
	inline EGodMode godmode_type = EGodMode::Full;

	inline bool speed_multiplier = true;
	inline float speed_multiplier_value = 10;

	inline bool sprint_multiplier = true;
	inline float sprint_multiplier_value = 15;

	inline bool omni_walk = false;

	inline bool gravity_scale;
	inline float gravity_scale_value;

	inline bool moon_walk;

	inline bool fire_rate = false;
	inline float fire_rate_value = 50;

	inline bool damage_modifier = true;
	inline float damage_modifier_value = 2500.f;
}