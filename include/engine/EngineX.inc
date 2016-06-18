/**********************************************************************************************************************************
 *                                                                                                                                *
 *                                            NGCM Mob Move Engine System 5.1 Delta X                                             *
 *                                                                                                                                *
 * Copyright � 2016 Abyss Morgan. All rights reserved.                                                                            *
 *                                                                                                                                *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/engine                                                      *
 *                                                                                                                                *
 * File Version: 5.1 X                                                                                                            *
 *                                                                                                                                *
 * Include created for the project Next Generation City Mod http://ngc.porobieni.com                                              *
 *                                                                                                                                *
 * Functions:                                                                                                                     *
 * bool:IsPointInWaterEx(Float:x,Float:y,Float:z);                                                                                *
 * GetClockPos(Float:x,Float:y,Float:z,Float:radius,&Float:tx,&Float:ty,&Float:tz,&Float:trz,Float:rz = -1000.0);                 *
 * EngineX(objectid,areaid,EngineX:engineid,minradius,maxradius,Float:minz,Float:speed);                                          *
 * EngineExcavatorUpdate(objectid,areaid,EngineX:engineid,Float:speed);                                                           *
 * DeltaEngineRotation(objectid,EngineX:engineid,Float:speed = 0.05);                                                             *
 * DeltaEngineX(objectid,areaid,EngineX:engineid,minradius,maxradius,Float:minz,Float:speed);                                     *
 *                                                                                                                                *
 **********************************************************************************************************************************/

/*
Why delta since the fifth version ?

1.0 - Do whatever you want. (Sphere)
2.0 Alpha - Turn, look straight ahead, fly. (Sphere)
3.0 Beta - Turn, look straight ahead, fly. (Area Cube)
4.0 Gamma X - Choose a direction, look straight ahead, fly. (Area Cube)
5.0 Delta X - Choose a direction, slowly turn, look straight ahead, fly. (Area Cube)

Why X ?
Do not ask XD
*/

#if defined NGCM_KERNEL
	#error Fatal error incompatible NOX
#endif

#if defined _NOX_ENGINE_X
	#endinput
#endif
#define _NOX_ENGINE_X


//Check Version 3DTryg.inc
#if !defined _3D_Tryg
	#error You need 3DTryg.inc v2.5C
#elseif !defined Tryg3D_Version
	#error Update you 3DTryg.inc to v2.5C
#elseif (Tryg3D_Version < 20503)
	#error Update you 3DTryg.inc to v2.5C
#endif

//Check MapAndreasEx.inc
#if !defined _Map_Andreas_Ex
	#error You need MapAndreasEx.inc
#endif

#define NOX_ENGINE_X_Version		(50124)
#define NOX_VERSION					"5.1 Delta X"
#define NT_VERSION					"1.0"

new InvalidPolygon[2],
	bool:EngineXLoaded = false;

enum e_nox_float {
	Float:X,
	Float:Y,
	Float:Z,
	Float:rX,
	Float:rY,
	Float:rZ,
	Float:tX,
	Float:tY,
	Float:tZ
}

forward OnEngineXInit();
forward OnEngineXExit();

public OnEngineXInit(){
	SafeMapAndreasInit();
	if(!IsMapAndreasInit()){
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			printf("[ADM] Error: Invalid MapAndreas Memory.");
			printf("[ADM] Error: NGCM Mob Move Engine System %s not loaded.",NOX_VERSION);
		}
		return 0;
	}
	InvalidPolygon[0] = CreateDynamicRectangle(398.0,689.0,808.0,1031.0,-1,-1,-1);		//Kanion blokada
	InvalidPolygon[1] = CreateDynamicRectangle(-1407.0,1979.0,-445.0,2843.0,-1,-1,-1);	//Tama Blokada
	if(GetSVarInt("ADM:Logging:Disable") == 0){
		printf("[ADM] Info: NGCM Mob Move Engine System %s loaded",NOX_VERSION);
	}
	EngineXLoaded = true;
	return 1;
}

public OnEngineXExit(){
	if(!EngineXLoaded) return 0;
	if(IsValidDynamicArea(InvalidPolygon[0])) DestroyDynamicArea(InvalidPolygon[0]);
	if(IsValidDynamicArea(InvalidPolygon[1])) DestroyDynamicArea(InvalidPolygon[1]);
	if(GetSVarInt("ADM:Logging:Disable") == 0){
		printf("[ADM] Info: NGCM Mob Move Engine System %s unloaded.",NOX_VERSION);
	}
	EngineXLoaded = false;
	return 1;
}

public OnFilterScriptInit(){
	OnEngineXInit();
	#if defined NOX_OnFilterScriptInit
		NOX_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit NOX_OnFilterScriptInit
#if defined NOX_OnFilterScriptInit
	forward NOX_OnFilterScriptInit();
#endif

public OnFilterScriptExit(){
	OnEngineXExit();
	#if defined NOX_OnFilterScriptExit
		NOX_OnFilterScriptExit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit NOX_OnFilterScriptExit
#if defined NOX_OnFilterScriptExit
	forward NOX_OnFilterScriptExit();
#endif

public OnGameModeInit(){
	OnEngineXInit();
	#if defined NOX_OnGameModeInit
		NOX_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit NOX_OnGameModeInit
#if defined NOX_OnGameModeInit
	forward NOX_OnGameModeInit();
#endif

public OnGameModeExit(){
	OnEngineXExit();
	#if defined NOX_OnGameModeExit
		NOX_OnGameModeExit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit NOX_OnGameModeExit
#if defined NOX_OnGameModeExit
	forward NOX_OnGameModeExit();
#endif

//Engine ID
#define ENGINE_NORMAL 					(EngineX:0)		//[Object: 1681, 18846 OR ANY] 	|| 5.0 Delta X
#define ENGINE_FIGHTER					(EngineX:1)		//[Object: 10757]				|| 5.0 Delta X
#define ENGINE_SUPPLY					(EngineX:2)		//[Object: 1683, 3528]			|| 5.0 Delta X
//#define ENGINE_NGCMS					(EngineX:3)		//[] (Only NGCM)				|| 4.0 X
//#define ENGINE_ARCMS					(EngineX:4)		//[] (Only NGCM)				|| 4.0 X
//#define ENGINE_COMMANDER				(EngineX:5)		//[] (Only NGCM)				|| 4.0 X
#define ENGINE_ELITE					(EngineX:6)		//[Object: 14553] 				|| 5.0 Delta X
#define ENGINE_UBOOT					(EngineX:7)		//[Object: 9958]				|| 5.0 Delta X
#define ENGINE_SHIP						(EngineX:8)		//[Object: 8493]				|| 4.0 X (not recommended to use version 5.0)
#define ENGINE_MINI						(EngineX:9)		//[Object: 2510, 2512]			|| 5.0 Delta X
#define ENGINE_EXCAVATOR 				(EngineX:10)	//[Object: 18248]				|| 4.1 G (Ground)
#define ENGINE_UNDERDUDE				(EngineX:11)	//[Object: 1379]				|| 5.1 U (Underwater)

//DeltaEngineRotation Speed
#define DELTA_ENGINE_SPEED_NORMAL 		(0.050)
#define DELTA_ENGINE_SPEED_FIGHTER		(0.050)
#define DELTA_ENGINE_SPEED_SUPPLY		(0.020)
//#define DELTA_ENGINE_SPEED_NGCMS		(0.050)
//#define DELTA_ENGINE_SPEED_ARCMS		(0.050)
//#define DELTA_ENGINE_SPEED_COMMANDER	(0.050)
#define DELTA_ENGINE_SPEED_ELITE		(0.010)
#define DELTA_ENGINE_SPEED_UBOOT		(0.005)
#define DELTA_ENGINE_SPEED_SHIP			(0.050)
#define DELTA_ENGINE_SPEED_MINI			(0.050)
//#define DELTA_ENGINE_SPEED_EXCAVATOR	(0.001)
#define DELTA_ENGINE_SPEED_UNDERDUDE	(0.050)

stock bool:IsPointInWaterEx(Float:x,Float:y,Float:z){
	if(!EngineXLoaded) return false;
	if(IsPointInDynamicArea(InvalidPolygon[0],x,y,z)) return false;
	if(IsPointInDynamicArea(InvalidPolygon[1],x,y,z)) return false;
	return true;
}

stock GetClockPos(Float:x,Float:y,Float:z,Float:radius,&Float:tx,&Float:ty,&Float:tz,&Float:trz,Float:rz = -1000.0){
	if(!EngineXLoaded) return 0;
	GetRandomClockPos(x,y,z,radius,tx,ty,tz,trz,rz);
	new Float:tmpz;
	MapAndreasFindZ(tx,ty,tmpz);
	if(tz < tmpz+50.0){
		tz += 50.0;
	}
	return 1;
}

stock EngineX(objectid,areaid,EngineX:engineid,minradius,maxradius,Float:minz,Float:speed){
	if(!EngineXLoaded) return 0;
	new rad = maxradius-minradius, F5[e_nox_float];
	if(rad <= 0) rad = 1;
	
	switch(engineid){
	
		case ENGINE_NORMAL: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRX = random(91)-45, randRZ = random(360), randR = random(rad)+minradius;
				GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
				GetPointInFront3D(F5[X],F5[Y],F5[Z],randRX,randRZ,randR,F5[tX],F5[tY],F5[tZ]);
				if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					MapAndreasFindZ(F5[tX],F5[tY],tmpz);
					if(tmpz+minz < F5[tZ]){
						MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,randRX,0.0,randRZ);
					}
				}
			}
		}
		
		case ENGINE_FIGHTER: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRX = random(91)-45, randRZ = random(360), randR = random(rad)+minradius, tmpRX, tmpRZ;
				GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
				CompRotation((-1)*(randRX+8),tmpRX);
				CompRotation(randRZ-180,tmpRZ);
				GetPointInFront3D(F5[X],F5[Y],F5[Z],tmpRX,tmpRZ,randR,F5[tX],F5[tY],F5[tZ]);
				if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					MapAndreasFindZ(F5[tX],F5[tY],tmpz);
					if(tmpz+minz < F5[tZ]){
						MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,randRX+8,12.0,randRZ);
					}
				}
			}
		}
		
		case ENGINE_SUPPLY: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRX = random(91)-45, randRZ = random(360), randR = random(rad)+minradius, tmpRX, tmpRZ;
				GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
				CompRotation((-1)*(randRX),tmpRX);
				CompRotation(randRZ-90,tmpRZ);
				GetPointInFront3D(F5[X],F5[Y],F5[Z],tmpRX,tmpRZ,randR,F5[tX],F5[tY],F5[tZ]);
				if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					MapAndreasFindZ(F5[tX],F5[tY],tmpz);
					if(tmpz+minz < F5[tZ]){
						MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,0.0,randRX,randRZ);
					}
				}
			}
		}
		
		case ENGINE_ELITE: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRX = random(91)-45, randRZ = random(360), randR = random(rad)+minradius, tmpRX, tmpRZ;
				GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
				CompRotation((-1)*(randRX+14),tmpRX);
				CompRotation(randRZ-180,tmpRZ);
				GetPointInFront3D(F5[X],F5[Y],F5[Z],tmpRX,tmpRZ,randR,F5[tX],F5[tY],F5[tZ]);
				if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					MapAndreasFindZ(F5[tX],F5[tY],tmpz);
					if(tmpz+minz < F5[tZ]){
						MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,randRX+14,12.0,randRZ);
					}
				}
			}
		}
		
		case ENGINE_UBOOT: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRZ = random(360), randR = random(rad)+minradius, tmpRZ;
				GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
				CompRotation(randRZ-180,tmpRZ);
				GetPointInFront3D(F5[X],F5[Y],F5[Z],0.0,tmpRZ,randR,F5[tX],F5[tY],F5[tZ]);
				if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					MapAndreasFindZ(F5[tX],F5[tY],tmpz);
					if(tmpz == 0.0 && IsPointInWaterEx(F5[tX],F5[tY],tmpz)){
						MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,0.0,0.0,randRZ);
					}
				}
			}
		}
		
		case ENGINE_SHIP: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRZ = random(360), randR = random(rad)+minradius;
				GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
				GetPointInFront3D(F5[X],F5[Y],F5[Z],0.0,randRZ,randR,F5[tX],F5[tY],F5[tZ]);
				if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					MapAndreasFindZ(F5[tX],F5[tY],tmpz);
					if(tmpz == 0.0 && IsPointInWaterEx(F5[tX],F5[tY],tmpz)){
						MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,0.0,0.0,randRZ);
					}
				}
			}
		}
	
		case ENGINE_MINI: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRX = random(91)-45, randRZ = random(360), randR = random(rad)+minradius, tmpRX, tmpRZ;
				GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
				CompRotation((-1)*(randRX),tmpRX);
				CompRotation(randRZ-180,tmpRZ);
				GetPointInFront3D(F5[X],F5[Y],F5[Z],tmpRX,tmpRZ,randR,F5[tX],F5[tY],F5[tZ]);
				if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					MapAndreasFindZ(F5[tX],F5[tY],tmpz);
					if(tmpz+minz < F5[tZ]){
						MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,randRX,0.0,randRZ);
					}
				}
			}
		}
		
		case ENGINE_EXCAVATOR: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRZ = random(360), randR = random(rad)+minradius, tmpRZ;
				GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
				CompRotation(randRZ-180,tmpRZ);
				GetPointInFront3D(F5[X],F5[Y],F5[Z],0.0,tmpRZ,randR,F5[tX],F5[tY],F5[tZ]);				
				if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					MapAndreasFindZ(F5[tX],F5[tY],tmpz);
					if(tmpz > 0.0){
						Streamer_SetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_EXTRA_ID,randRZ);
						MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,0.0,0.0,randRZ);
					}
				}
			}
		}
		
		case ENGINE_UNDERDUDE: {
			if(!IsDynamicObjectMoving(objectid)){
				new randRX = random(51)-25, randRZ = random(360), randR = random(rad)+minradius;
				GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
				GetPointInFront3D(F5[X],F5[Y],F5[Z],randRX,randRZ,randR,F5[tX],F5[tY],F5[tZ]);
				if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
					new Float:tmpz;
					MapAndreasFindZ(F5[tX],F5[tY],tmpz);
					if(tmpz == 0.0 && F5[tZ] < 0.0 && IsPointInWaterEx(F5[tX],F5[tY],tmpz)){
						MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,randRX,0.0,randRZ);
					}
				}
			}
		}
		
	}
	return 1;
}

stock EngineExcavatorUpdate(objectid,areaid,EngineX:engineid,Float:speed){
	if(!EngineXLoaded) return 0;
	new F5[e_nox_float];
	switch(engineid){
		case ENGINE_EXCAVATOR: {
			if(IsDynamicObjectMoving(objectid)){
				new randRZ;
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_X,F5[tX]);
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_Y,F5[tY]);
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MOVE_Z,F5[tZ]);
				randRZ = Streamer_GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_EXTRA_ID);
				if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
					GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
					MapAndreasFindZ(F5[X],F5[Y],F5[Z]);
					F5[Z] += 7.0;
					MoveDynamicObject(objectid,F5[tX],F5[tY],F5[Z],speed,0.0,0.0,randRZ);
				}
			}
		}
	}
	return 1;
}

stock DeltaEngineRotation(objectid,EngineX:engineid,Float:speed = 0.050){
	if(!EngineXLoaded) return 0;
	new F5[e_nox_float];
	
	GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
	if(engineid == ENGINE_UNDERDUDE){
		F5[rX] = random(51)-25;
		F5[rY] = 0.0;
	} else {
		F5[rX] = random(91)-45;
		F5[rY] = random(20)-10;
	}
	F5[rZ] = random(360);
	
	if(engineid == ENGINE_SHIP || engineid == ENGINE_UBOOT){
		if(F5[Z] > 0.0){
			F5[Z]-=0.05;
		} else {
			F5[Z]+=0.05;
		}
	} else {
		F5[Z]+=0.05;
	}
	
	switch(engineid){
		case ENGINE_NORMAL: {
			MoveDynamicObject(objectid,F5[X],F5[Y],F5[Z],speed,F5[rX],F5[rY],F5[rZ]);
		}
		case ENGINE_FIGHTER: {
			MoveDynamicObject(objectid,F5[X],F5[Y],F5[Z],speed,F5[rX]+8.0,F5[rY]+12.0,F5[rZ]);
		}
		case ENGINE_SUPPLY: {
			MoveDynamicObject(objectid,F5[X],F5[Y],F5[Z],speed,F5[rY],F5[rX],F5[rZ]);
		}
		case ENGINE_ELITE: {
			MoveDynamicObject(objectid,F5[X],F5[Y],F5[Z],speed,F5[rX]+14.0,F5[rY]+12.0,F5[rZ]);
		}
		case ENGINE_UBOOT: {
			MoveDynamicObject(objectid,F5[X],F5[Y],F5[Z],speed,0.0,0.0,F5[rZ]);
		}
		case ENGINE_SHIP: {
			MoveDynamicObject(objectid,F5[X],F5[Y],F5[Z],speed,0.0,0.0,F5[rZ]);
		}
		case ENGINE_MINI: {
			MoveDynamicObject(objectid,F5[X],F5[Y],F5[Z],speed,F5[rX],F5[rY],F5[rZ]);
		}
		/*
		//Invalid
		case ENGINE_EXCAVATOR: {
			Streamer_SetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_EXTRA_ID,floatround(F5[rZ]));
			MoveDynamicObject(objectid,F5[X],F5[Y],F5[Z],speed,0.0,0.0,F5[rZ]-180.0);
		}
		*/
		case ENGINE_UNDERDUDE: {
			MoveDynamicObject(objectid,F5[X],F5[Y],F5[Z],speed,F5[rX],F5[rY],F5[rZ]);
		}
	}
	return 1;
}

stock DeltaEngineX(objectid,areaid,EngineX:engineid,minradius,maxradius,Float:minz,Float:speed){
	if(!EngineXLoaded) return 0;
	new rad = maxradius-minradius, F5[e_nox_float];
	if(rad <= 0) rad = 1;
	
	switch(engineid){
	
		case ENGINE_NORMAL: {
			new randR = random(rad)+minradius;
			GetDynamicObjectRot(objectid,F5[rX],F5[rY],F5[rZ]);
			GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
			GetPointInFront3D(F5[X],F5[Y],F5[Z],F5[rX],F5[rZ],randR,F5[tX],F5[tY],F5[tZ]);
			if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				MapAndreasFindZ(F5[tX],F5[tY],tmpz);
				if(tmpz+minz < F5[tZ]){
					MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,F5[rX],F5[rY],F5[rZ]);
				}
			}
		}
		
		case ENGINE_FIGHTER: {
			new randR = random(rad)+minradius, Float:tmpRX, Float:tmpRZ;
			GetDynamicObjectRot(objectid,F5[rX],F5[rY],F5[rZ]);
			GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
			CompRotationFloat((-1)*(F5[rX]+8),tmpRX);
			CompRotationFloat(F5[rZ]-180,tmpRZ);
			GetPointInFront3D(F5[X],F5[Y],F5[Z],tmpRX,tmpRZ,randR,F5[tX],F5[tY],F5[tZ]);
			if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				MapAndreasFindZ(F5[tX],F5[tY],tmpz);
				if(tmpz+minz < F5[tZ]){
					MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,F5[rX],F5[rY],F5[rZ]);
				}
			}
		}
		
		case ENGINE_SUPPLY: {
			new randR = random(rad)+minradius, Float:tmpRX, Float:tmpRZ;
			GetDynamicObjectRot(objectid,F5[rX],F5[rY],F5[rZ]);
			GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
			CompRotationFloat((-1)*(F5[rY]),tmpRX);
			CompRotationFloat(F5[rZ]-90,tmpRZ);
			GetPointInFront3D(F5[X],F5[Y],F5[Z],tmpRX,tmpRZ,randR,F5[tX],F5[tY],F5[tZ]);
			if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				MapAndreasFindZ(F5[tX],F5[tY],tmpz);
				if(tmpz+minz < F5[tZ]){
					MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,F5[rX],F5[rY],F5[rZ]);
				}
			}
		}
		
		case ENGINE_ELITE: {
			new randR = random(rad)+minradius, Float:tmpRX, Float:tmpRZ;
			GetDynamicObjectRot(objectid,F5[rX],F5[rY],F5[rZ]);
			GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
			CompRotationFloat((-1)*(F5[rX]+14.0),tmpRX);
			CompRotationFloat(F5[rZ]-180.0,tmpRZ);
			GetPointInFront3D(F5[X],F5[Y],F5[Z],tmpRX,tmpRZ,randR,F5[tX],F5[tY],F5[tZ]);
			if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				MapAndreasFindZ(F5[tX],F5[tY],tmpz);
				if(tmpz+minz < F5[tZ]){
					MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,F5[rX],F5[rY],F5[rZ]);
				}
			}
		}
		
		case ENGINE_UBOOT: {
			new randR = random(rad)+minradius, Float:tmpRZ;
			GetDynamicObjectRot(objectid,F5[rX],F5[rY],F5[rZ]);
			GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
			CompRotationFloat(F5[rZ]-180.0,tmpRZ);
			GetPointInFront2D(F5[X],F5[Y],tmpRZ,randR,F5[tX],F5[tY]);
			if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				MapAndreasFindZ(F5[tX],F5[tY],tmpz);
				if(tmpz == 0.0 && IsPointInWaterEx(F5[tX],F5[tY],tmpz)){
					MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,0.0,0.0,F5[rZ]);
				}
			}
		}
		
		case ENGINE_SHIP: {
			new randR = random(rad)+minradius;
			GetDynamicObjectRot(objectid,F5[rX],F5[rY],F5[rZ]);
			GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
			GetPointInFront3D(F5[X],F5[Y],F5[Z],0.0,F5[rZ],randR,F5[tX],F5[tY],F5[tZ]);
			if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				MapAndreasFindZ(F5[tX],F5[tY],tmpz);
				if(tmpz == 0.0 && IsPointInWaterEx(F5[tX],F5[tY],tmpz)){
					MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,0.0,0.0,F5[rZ]);
				}
			}
		}
	
		case ENGINE_MINI: {
			new randR = random(rad)+minradius, Float:tmpRX, Float:tmpRZ;
			GetDynamicObjectRot(objectid,F5[rX],F5[rY],F5[rZ]);
			GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
			CompRotationFloat((-1)*(F5[rX]),tmpRX);
			CompRotationFloat(F5[rZ]-180.0,tmpRZ);
			GetPointInFront3D(F5[X],F5[Y],F5[Z],tmpRX,tmpRZ,randR,F5[tX],F5[tY],F5[tZ]);
			if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				MapAndreasFindZ(F5[tX],F5[tY],tmpz);
				if(tmpz+minz < F5[tZ]){
					MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,F5[rX],F5[rY],F5[rZ]);
				}
			}
		}
		
		/*
		//Invalid
		case ENGINE_EXCAVATOR: {
			new randR = random(rad)+minradius, Float:tmpRZ;
			GetDynamicObjectRot(objectid,F5[rX],F5[rY],F5[rZ]);
			GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
			CompRotationFloat(F5[rZ]-180.0,tmpRZ);
			GetPointInFront3D(F5[X],F5[Y],F5[Z],0.0,tmpRZ,randR,F5[tX],F5[tY],F5[tZ]);
			if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				MapAndreasFindZ(F5[tX],F5[tY],tmpz);
				if(tmpz > 0.0){
					MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,0.0,0.0,F5[rZ]);
				}
			}
		}
		*/
		
		case ENGINE_UNDERDUDE: {
			new randR = random(rad)+minradius;
			GetDynamicObjectRot(objectid,F5[rX],F5[rY],F5[rZ]);
			GetDynamicObjectPos(objectid,F5[X],F5[Y],F5[Z]);
			GetPointInFront3D(F5[X],F5[Y],F5[Z],F5[rX],F5[rZ],randR,F5[tX],F5[tY],F5[tZ]);
			if((IsPointInDynamicArea(areaid,F5[tX],F5[tY],F5[tZ])) && (IsValidDynamicObject(objectid))){
				new Float:tmpz;
				MapAndreasFindZ(F5[tX],F5[tY],tmpz);
				if(tmpz == 0.0 && F5[tZ] < 0.0 && IsPointInWaterEx(F5[tX],F5[tY],tmpz)){
					MoveDynamicObject(objectid,F5[tX],F5[tY],F5[tZ],speed,F5[rX],F5[rY],F5[rZ]);
				}
			}
		}
		
	}
	return 1;
}

//EOF