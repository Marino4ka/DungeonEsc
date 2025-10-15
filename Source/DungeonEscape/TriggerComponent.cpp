// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (MoverActor)
	{
		Mover = MoverActor->FindComponentByClass<UMover>();
		if (Mover)
		{
			UE_LOG(LogTemp, Display, TEXT("Succesfully found the mover component!"));
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Failed to found the mover component!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Mover is nullptr!"));
	}

	if(IsPressurePlate)
	{
		OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapBegin);
		OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapEnd);
	}

	
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UTriggerComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("PressurePlateActivator"))
	{
		ActivatorCount++;

		if(!IsTriggered)
		{
			TriggerChange(true);
			UE_LOG(LogTemp, Display, TEXT("OnOverlapBegin triggered"));

		}
		
	}
}


void UTriggerComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor && OtherActor->ActorHasTag("PressurePlateActivator"))
	{
		ActivatorCount--;

		if (IsTriggered && (ActivatorCount == 0))
		{
			TriggerChange(false);
			UE_LOG(LogTemp, Display, TEXT("OnOverlapEnd triggered"));

		}
		
		
	}
}


void UTriggerComponent::TriggerChange(bool NewTriggerValue)
{
	IsTriggered = NewTriggerValue;
	UE_LOG(LogTemp, Display, TEXT("TriggerChange called"));

	
	if(Mover)
		{
			Mover->SetShouldMove(IsTriggered);
			UE_LOG(LogTemp, Display, TEXT("TriggerChange mover exist"));

		}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("%s doesn't have a mover to trigger!"), *GetOwner()->GetActorNameOrLabel() );
	}
}
