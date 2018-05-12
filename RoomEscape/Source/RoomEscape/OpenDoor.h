// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TriggerVolume.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"      // must be the last include 



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOMESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void CloseDoor();

	void OpenDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere)
	float openAngle = 60;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* triggerPlate;
	
	UPROPERTY(EditAnywhere)
	AActor* actorThatOpens; // the player can open the door
};
