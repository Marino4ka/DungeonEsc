// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	/*AActor* MyOwner = GetOwner();
	FVector CurrentLocation = MyOwner->GetActorLocation();
	UE_LOG(LogTemp, Display, TEXT("StartLocation is: %s"), *StartLocation.ToCompactString());
	UE_LOG(LogTemp, Display, TEXT("CurrentLocation is: %s"), *CurrentLocation.ToCompactString());*/
	
	//UE_LOG(LogTemp, Display, TEXT("My owner is: %s"), *GetOwner()->GetActorNameOrLabel());
	
	StartLocation = GetOwner() -> GetActorLocation();
	SetShouldMove(false);
	//UE_LOG(LogTemp, Display, TEXT("Location is: %s"), *StartLocation.ToCompactString());

	//TargetLocation = StartLocation + MoveOffset;


	/*UE_LOG(LogTemp, Display, TEXT("Owner is: %s"), *MyOwner->GetActorNameOrLabel());*/




	//float MyFloat = 10.0f;
	//float* FloatPtr = &MyFloat;

	//float Result = *FloatPtr + 5.0f;
	//UE_LOG(LogTemp, Display, TEXT("Result: %f"), Result);

	//*FloatPtr = 30.0f;
	//UE_LOG(LogTemp, Display, TEXT("MyFloat: %f"), MyFloat);
	//UE_LOG(LogTemp, Display, TEXT("*FloatPtr: %f"), *FloatPtr);
	//UE_LOG(LogTemp, Display, TEXT("FloatPtr: %p"), FloatPtr);
	//UE_LOG(LogTemp, Display, TEXT("&MyFloat: %p"), &MyFloat);

	//FVector MyVector = FVector(1.0f, 1.0f, 1.0f);

	//FVector* MyVectorPtr = &MyVector;

	//MyVectorPtr -> X = 2.0f;
	//MyVectorPtr -> Y = 3.0f;
	//MyVectorPtr -> Z = 4.0f;

	////FString MyVectorString = MyVector.ToCompactString();
	//FString MyVectorString = MyVectorPtr ->ToCompactString();


	//UE_LOG(LogTemp, Display, TEXT("MyVector: %s"), *MyVectorString);
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	FVector CurrentLocation = GetOwner()->GetActorLocation();
	ReachedTarget = CurrentLocation.Equals(TargetLocation);

	if(!ReachedTarget)
	{
		float Speed = MoveOffset.Length()/MoveTime;

		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);

		GetOwner()->SetActorLocation(NewLocation);
	}



	//CurrentLocation.Z = CurrentLocation.Z + 100.0f * DeltaTime;
	// GetOwner()->SetActorLocation(CurrentLocation);
	
}

bool UMover:: GetShouldMove()
{
	return ShouldMove;
}

void UMover::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;

if (ShouldMove)
{
	TargetLocation = StartLocation + MoveOffset;
}
else
{
	TargetLocation = StartLocation;
}

}

