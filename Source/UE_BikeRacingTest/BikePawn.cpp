// BikePawn.cpp
#include "BikePawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
ABikePawn::ABikePawn()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create the skeletal mesh for the bike
    BikeMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BikeMesh"));
    RootComponent = BikeMesh;

    // Create and attach the spring arm
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);

    // Create and attach the camera
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

    // Add the pawn movement component
    MovementComponent = CreateDefaultSubobject<UMovementComponent>(TEXT("MovementComponent"));

    // Auto possess player
    //AutoPossessPlayer = EAutoReceiveInput::Player0;

    // Set default values for camera controls
    LookUpRate = 45.0f;
    TurnRate = 45.0f;
}

// Called when the game starts or when spawned
void ABikePawn::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ABikePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABikePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Bind input axes
    PlayerInputComponent->BindAxis("MoveForward", this, &ABikePawn::MoveForward);
    PlayerInputComponent->BindAxis("TurnRight", this, &ABikePawn::TurnRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ABikePawn::LookUp);
    PlayerInputComponent->BindAxis("Turn", this, &ABikePawn::Turn);
}

void ABikePawn::MoveForward(float Value)
{
    if (Controller && Value != 0.0f)
    {
        FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void ABikePawn::TurnRight(float Value)
{
    if (Controller && Value != 0.0f)
    {
        FRotator NewRotation = GetActorRotation();
        NewRotation.Yaw += Value;
        SetActorRotation(NewRotation);
    }
}

void ABikePawn::LookUp(float Value)
{
    if (Controller)
    {
        AddControllerPitchInput(Value * LookUpRate * GetWorld()->GetDeltaSeconds());
    }
}

void ABikePawn::Turn(float Value)
{
    if (Controller)
    {
        AddControllerYawInput(Value * TurnRate * GetWorld()->GetDeltaSeconds());
    }
}
