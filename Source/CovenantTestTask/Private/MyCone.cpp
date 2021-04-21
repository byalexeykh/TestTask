// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCone.h"

AMyCone::AMyCone() {
	PrimitiveType = EPrimitive::Cone;
	Mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Primitive/Shapes/Shape_Cone.Shape_Cone")).Object;
	StaticMeshComp->SetStaticMesh(Mesh);
}