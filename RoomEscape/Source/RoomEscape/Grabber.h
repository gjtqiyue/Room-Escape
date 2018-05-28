// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOMESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	

	

private:
	// How far ahead of the player can reach
	float Reach = 100;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;

	// Grab what is in reach
	void Grab();

	// Release what is grabbing
	// Called when the grab key is released
	void Release();

	void FindPhysicsHandleComponent();

	void SetUpInputComponent();

	// Return the hit result
	const FHitResult GetFirstPhysicsBodyInReach();

	FVector GetReachedLineEnd();

	FVector GetReachedLineStart();
};
