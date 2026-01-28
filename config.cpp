class CfgPatches
{
	class subject
	{
		units[] =
			{
				"Specimen_RO9",
				"Crate"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] =
			{
				"DZ_Characters", "DZ_Characters_Zombies", "DZ_Gear_Containers"};
	};
};
class CfgMods
{
	class Specimen_RO9
	{
		type = "mod";
		dependencies[] =
			{
				"World"};
		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] =
					{
						"subject\scripts\4_world"};
			};
		};
	};
};
class CfgSoundShaders
{
	class Subject_Breathing_Shader
	{
		samples[] = {{"subject\sounds\breath.ogg", 1}};
		volume = 1.3;
		range = 40;
	};
	class Subject_Groan_Shader
	{
		samples[] = {
			{"subject\sounds\roar.ogg", 1}};
		volume = 1.0;
		range = 100;
	};
	class Subject_Attack_Shader
	{
		samples[] = {{"subject\sounds\attack.ogg", 1}};
		volume = 0.7;
		range = 50;
	};
};
class CfgSoundSets
{
	class Subject_Groan_Set
	{
		soundShaders[] = {"Subject_Groan_Shader"};
		volumeFactor = 1.0;
		spatial = 1;
	};
	class Subject_Attack_Set
	{
		soundShaders[] = {"Subject_Attack_Shader"};
		volumeFactor = 0.7;
		spatial = 1;
	};
	class Subject_Breathing_Set
	{
		soundShaders[] = {"Subject_Breathing_Shader"};
		volumeFactor = 1.3;
		spatial = 1;
		looping = 0;
	};
};
class CfgSoundLookupTables
{
	class Subject_Groan_LookupTable
	{
		soundSets[] = {"Subject_Groan_Set"};
	};
	class Subject_Attack_LookupTable
	{
		soundSets[] = {"Subject_Attack_Set"};
	};
};
class CfgVehicles
{
	class AnimEvents;
	class ZmbM_usSoldier_normal_Base;
	class DamageSystem;
	class Inventory_Base;
	class Specimen_Head : Inventory_Base
	{
		scope = 2;
		displayName = "Specimen R-09 Head";
		descriptionShort = "The head of a failed bio-experiment exhibiting extreme anatomical distortion. This is truly disgusting.";
		model = "subject\models\specimen_Head.p3d";
		weight = 130;
		itemSize[] = {3, 3};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 50000;
				};
			};
		};
	};
	class Container_Base;
	class Crate : Container_Base
	{
		scope = 2;
		displayName = "R09 Loot Holder";
		model = "subject\models\crate.p3d";
		itemBehaviour = 2;
		canBeTaken = 0;
		canBeHeld = 0;

		class Cargo
		{
			itemsCargoSize[] = {5, 10};
			allowOwnedCargoManipulation = 1;
			openable = 0;
			cargoType = "Container";
			isStatic = 1;
		};
	};
	class Specimen_RO9 : ZmbM_usSoldier_normal_Base
	{
		scope = 2;
		model = "subject\models\specimen.p3d";
		displayName = "Specimen R-09";
		descriptionShort = "A failed bio-experiment exhibiting extreme anatomical distortion. Highly aggressive. Detects movement and sound. Avoid close contact.";
		aiAgentTemplate = "InfectedMSoldier";
		hiddenSelectionsMaterials[] = {"subject\models\specimen.rvmat"};
		hiddenSelectionsTextures[] = {"subject\data\subject_co.paa"};
		allowOwnedCargoManipulation = 1;

		DamageSphereAmmos[] =
			{
				"MeleeZombieMale"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 2500;
				};
			};
		};
		class AnimEvents : AnimEvents
		{
			class SoundVoice
			{
				class Attack
				{
					soundSet = "Subject_Attack_Set";
					id = 5;
				};
				class CallToArmsShort
				{
					soundSet = "Subject_Groan_Set";
					id = 20;
				};
			};
		};
	};
};