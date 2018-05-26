// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();

	SetUpInputComponent();
}

void UGrabber::FindPhysicsHandleComponent() {
	/// Look for attached Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle) {

	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *(GetOwner()->GetName()));
	}
}

void UGrabber::SetUpInputComponent() {
	/// Look for attached Input Component
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent) {
		/// Bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *(GetOwner()->GetName()));
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	// Get payer view point this thick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	FVector LineTracedEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	/// draw a red trace in the world to viualise
	//DrawDebugLine(
	//	GetWorld(),
	//	PlayerViewPointLocation,
	//	LineTracedEnd,
	//	FColor(255, 0, 0), // pure red color
	//	false,
	//	0.f, 
	//	0.f,
	//	10.f // thickness
	//	);

	/// Set up the quary
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	/// Ray-cast out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit, // hit result
		PlayerViewPointLocation,
		LineTracedEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	/// See what it hits
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Hit result is %s"), *(ActorHit->GetName()));
	}

	return Hit;
}

void UGrabber::Grab() {
	//UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));

	auto ComponentToGrab = GetFirstPhysicsBodyInReach().GetComponent();
	auto HitActor = GetFirstPhysicsBodyInReach().GetActor();

	// Try and reach any actors with physics body collision channel set

	// If we hit something then attach a physics handle
	if (HitActor) {
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true // allow rotation
		);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released"));
	// Release handle
	PhysicsHandle->ReleaseComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get payer view point this thick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	FVector LineTracedEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	// If the handle is attached
	if (PhysicsHandle->GrabbedComponent) {
		// Move the object we are holding
		PhysicsHandle->SetTargetLocation(LineTracedEnd);
	}
	
}

