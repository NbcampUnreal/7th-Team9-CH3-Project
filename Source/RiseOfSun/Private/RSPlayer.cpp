#include "RSPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RSRifleSceneComponent.h"

#include "Components/StaticMeshComponent.h"

#include "Components/SceneComponent.h"

#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

ARSPlayer::ARSPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh>
		PlayerSkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Asset/Character/QuantumCharacter/Mesh/SKM_QuantumCharacter.SKM_QuantumCharacter'"));

	if (PlayerSkeletalMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(PlayerSkeletalMesh.Object);
		GetMesh()->SetWorldLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));

	}
	
	bUseControllerRotationYaw = true;

	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	if (MoveComp)
	{
		MoveComp->bOrientRotationToMovement = false;
	}
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	if (SpringArm)
	{
		SpringArm->SetupAttachment(RootComponent);
		SpringArm->SetWorldLocation(FVector(0, 0, 55));
		SpringArm->TargetArmLength = 100;
		SpringArm->SocketOffset = FVector(0, 40, 30);
		SpringArm->bUsePawnControlRotation = true;
	}
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	if (Camera)
	{
		Camera->SetupAttachment(SpringArm);
	}


	static ConstructorHelpers::FObjectFinder<UInputMappingContext>InputContext(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Default.IMC_Default'"));
	if (InputContext.Object != nullptr)
	{
		DefaultContext = InputContext.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction>InputMove(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Move.IA_Move'"));
	if (InputMove.Object != nullptr)
	{
		MoveAction = InputMove.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction>InputLook(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Look.IA_Look'"));
	if (InputLook.Object != nullptr)
	{
		LookAction = InputLook.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>InputFire(TEXT("/Game/Input/Actions/IA_Fire.IA_Fire"));
	if (InputFire.Object != nullptr)
	{
		FireAction = InputFire.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>InputAim(TEXT("/Game/Input/Actions/IA_Aim.IA_Aim"));
	if (InputAim.Object != nullptr)
	{
		AimAction = InputAim.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>InputReloading(TEXT("/Game/Input/Actions/IA_Reloading.IA_Reloading"));
	if (InputReloading.Object != nullptr)
	{
		ReloadingAction = InputReloading.Object;
	}

	RifleComp = CreateDefaultSubobject<URSRifleSceneComponent>(TEXT("RifleComp"));
	RifleComp->SetupAttachment(RootComponent);

	RifleMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RifleMeshComp"));
	RifleMeshComp->SetupAttachment(RifleComp);

	MuzzlePoint = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzlePoint"));
	MuzzlePoint->SetupAttachment(RifleMeshComp);

	


	if (RifleComp)
	{
		
		
		//총을 손에 붙이기
		/*RifleComp->SetupAttachment(GetMesh(), FName("hand_rSocket"));*/
		RifleComp->SetRelativeLocation(FVector(0, 0, 0));
		RifleComp->SetRelativeRotation(FRotator(0, 0, 0));
	}
	//---------- EXP 초기값 ----------
	Level = 1;

	// 경험치 초기값 설정
	CurrentEXP = 0;
	MaxEXP = 100;

	Stat.AttackDamage = 250.0f;
	Stat.Defense = 30.0f;
}

void ARSPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(DefaultContext, 0);
		}
	}
	GetCharacterMovement()->MaxWalkSpeed = playerMoveSpeed; //캐릭터 속도

	if (HUDWidgetclass)
	{
		PlayerHUD = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetclass);

		if (PlayerHUD)
		{
			PlayerHUD->AddToViewport();
		}
	}
}

void ARSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("CurrentHp: %f"), Stat.CurrentHealth);
	UE_LOG(LogTemp, Warning, TEXT("CurrentEXP: %f"), CurrentEXP);

	static float DamageAccumulator = 0.f;
	DamageAccumulator += DeltaTime;

	if (DamageAccumulator >= 1.f)
	{
		HitDamage(1);
		DamageAccumulator = 0.f;
	}

	if (Stat.CurrentHealth <= 0.f && !bIsDead)
	{
		Die();
	}

	AddEXP(1 * DeltaTime);
}

void ARSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARSPlayer::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARSPlayer::Look);
	EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ARSPlayer::Fire);
	//에임 구현 미정
	EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &ARSPlayer::Aim);
	EnhancedInputComponent->BindAction(ReloadingAction, ETriggerEvent::Triggered, this, &ARSPlayer::Reloading);
}

FDamageResult ARSPlayer::Attack(ARSCharacter* Target)
{
	FDamageResult result = ARSCharacter::Attack(Target);
	return result;
}


void ARSPlayer::Move(const FInputActionValue& Value)
{
	const FVector2D Movement = Value.Get<FVector2D>(); //X : 좌, 우 Y: 앞, 뒤

	const FRotator ControlRot = Controller ? Controller->GetControlRotation() : FRotator::ZeroRotator;
	const FRotator YawOnly(0.f, ControlRot.Yaw, 0.f);

	const FVector Forward = UKismetMathLibrary::GetForwardVector(YawOnly);
	const FVector Right = UKismetMathLibrary::GetRightVector(YawOnly);

	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	if(Movement.Y!=-1)
	{ 
			MoveComp->bOrientRotationToMovement = true;
	}
	else
	{
		MoveComp->bOrientRotationToMovement = false;
	}
	

	AddMovementInput(Forward, Movement.Y);
	AddMovementInput(Right, Movement.X);

	
}

void ARSPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookAxisVector.X * GetWorld()->DeltaTimeSeconds * mouseSpeed);
	AddControllerPitchInput(-LookAxisVector.Y * GetWorld()->DeltaTimeSeconds * mouseSpeed);
}

void ARSPlayer::Fire(const FInputActionValue& Value)
{
	
		RifleComp->Fire(MuzzlePoint, MuzzleFlashSystem);
		
	
}

//에임 구현 미정
void ARSPlayer::Aim(const FInputActionValue& Value)
{
	//미정미정
}

void ARSPlayer::Reloading(const FInputActionValue& Value)
{
	RifleComp->Reload();
}
void ARSPlayer::AddEXP(float  ExpAmount)
{
	if (ExpAmount <= 0)
		return;

	CurrentEXP += ExpAmount;
	UE_LOG(LogTemp, Warning, TEXT("Current EXP: %f / %d"), CurrentEXP, MaxEXP);

	// 여러 레벨업 가능성까지 고려
	while (CurrentEXP >= MaxEXP)
	{
		CurrentEXP -= MaxEXP;
		LevelUp();
	}
	OnEXPChanged.Broadcast();
}

void ARSPlayer::LevelUp()
{
	Level++;

	Stat.CurrentHealth = FMath::Clamp(
		Stat.CurrentHealth + 20.f,
		0.f,
		Stat.MaxHealth
	);

	UE_LOG(LogTemp, Warning, TEXT("Level Up! Current Level: %d"), Level);
}
