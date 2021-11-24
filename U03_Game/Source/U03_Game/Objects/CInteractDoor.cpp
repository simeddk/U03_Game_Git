#include "CInteractDoor.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

ACInteractDoor::ACInteractDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent(this, &Scene, "Scene");
	CHelpers::CreateComponent(this, &Box, "Box", Scene);
	CHelpers::CreateComponent(this, &DoorFrame, "DoorFrame", Scene);
	CHelpers::CreateComponent(this, &Door, "Door", DoorFrame);

	UStaticMesh* doorFrameMesh;
	CHelpers::GetAsset<UStaticMesh>(&doorFrameMesh, "StaticMesh'/Game/DoorMesh/Props/SM_DoorFrame.SM_DoorFrame'");
	DoorFrame->SetStaticMesh(doorFrameMesh);

	UStaticMesh* doorMesh;
	CHelpers::GetAsset<UStaticMesh>(&doorMesh, "StaticMesh'/Game/DoorMesh/Props/SM_Door.SM_Door'");
	Door->SetStaticMesh(doorMesh);
	Door->SetRelativeLocation(FVector(0, 45, 0));

	Box->InitBoxExtent(FVector(150, 50, 100));
	Box->SetRelativeLocation(FVector(0, 0, 100));
	Box->SetCollisionProfileName("Trigger");


}

void ACInteractDoor::BeginPlay()
{
	Super::BeginPlay();
	
	Box->SetHiddenInGame(bHiddenInGame);
}

void ACInteractDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bOpening)
		Opening(DeltaTime);

	if (bClosing)
		Closing(DeltaTime);

}

void ACInteractDoor::Interact(const FVector& InForward)
{
	 float dot = InForward | Box->GetForwardVector();
	 Direction = FMath::Sign(dot);

	 Degree = Direction * MaxDegree;

	 if (bClosed)
	 {
		 bClosed = false;
		 bClosing = false;
		 bOpening = true;
	 }
	 else
	 {
		 bClosed = true;
		 bClosing = true;
		 bOpening = false;
	 }
}

void ACInteractDoor::Opening(float Delta)
{
	//TODO
}

void ACInteractDoor::Closing(float Delta)
{
}
