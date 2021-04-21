// Fill out your copyright notice in the Description page of Project Settings.


#include "MySphere.h"

AMySphere::AMySphere() {
	PrimitiveType = EPrimitive::Sphere;
	Mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Primitive/Shapes/Shape_Sphere.Shape_Sphere")).Object;
	StaticMeshComp->SetStaticMesh(Mesh);
}