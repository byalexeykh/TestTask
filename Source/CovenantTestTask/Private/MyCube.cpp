// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCube.h"

AMyCube::AMyCube() {
	PrimitiveType = EPrimitive::Cube;
	Mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Primitive/Shapes/Shape_Cube.Shape_Cube")).Object;
	StaticMeshComp->SetStaticMesh(Mesh);
}