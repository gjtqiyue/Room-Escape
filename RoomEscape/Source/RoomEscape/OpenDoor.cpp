// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	CloseDoor();
	
}






// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	// if the player is in the volume
	if (triggerPlate->IsOverlappingActor(actorThatOpens)) {
		// open the door
		OpenDoor();
		//UE_LOG(LogTemp, Warning, TEXT("open"));
	}
	else {

		CloseDoor();
	}
}

void UOpenDoor::OpenDoor()
{
	// find the owning actor
	AActor* owner = GetOwner();

	// create a rotator
	FRotator newRotation = FRotator(0.f, openAngle, 0.f);
	
	// set the rotation
	owner->SetActorRotation(newRotation);
}

void UOpenDoor::CloseDoor()
{
	AActor* owner = GetOwner();

	FRotator newRotation = FRotator(0.0f, 0.0f, 0.0f);

	owner->SetActorRotation(newRotation);
}