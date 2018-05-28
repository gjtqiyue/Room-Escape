// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	owner = GetOwner();
	
	if (!triggerPlate) {
		UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate trigger"), *(GetOwner()->GetName()));
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	// if the player is in the volume
	if (GetTotalMassOfActorsOnPlate() > MinMass) {
		// open the door
		OnOpenRequest.Broadcast();
		//UE_LOG(LogTemp, Warning, TEXT("open"));
	}
	else {
		// close the door
		OnCloseRequest.Broadcast();
	}


}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	float TotalMass = 0.f;

	// Find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	if (!triggerPlate) { return TotalMass; }
	triggerPlate->GetOverlappingActors(OUT OverlappingActors);

	// Calculate the total mass
	for (auto& Actor : OverlappingActors) {
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		TotalMass += PrimitiveComponent->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("Total mass is %f"), TotalMass);
	}

	return TotalMass;
}