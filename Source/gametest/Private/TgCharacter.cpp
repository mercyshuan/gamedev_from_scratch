// Fill out your copyright notice in the Description page of Project Settings.


#include "TgCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ATgCharacter::ATgCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true; //将弹簧臂的使用pawn旋转 选项开启
	SpringArmComp->SetupAttachment(RootComponent); //将弹簧臂绑定到根骨骼上
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp); //将相机绑定到弹簧臂上

	GetCharacterMovement()->bOrientRotationToMovement = true;  // pawn方向会倾向于朝着视角方向 
	bUseControllerRotationYaw = false;//将控制视角旋转选项 关闭
}

// Called when the game starts or when spawned
void ATgCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATgCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();//制作一个旋转器，可获得视角方向
	ControlRot.Pitch = 0.0f;//屏蔽pitch，roll的值
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), Value); //沿着任意向量移动角色，ControlRot.Vector() 获取旋转器的方向
}



void ATgCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();//制作一个旋转器，可获得视角方向
	ControlRot.Pitch = 0.0f;//屏蔽pitch，roll的值
	ControlRot.Roll = 0.0f;
	FVector RightVecotor = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y); 
	//FRotationMatrix将某种旋转转换为旋转矩阵，乘以坐标轴，即可计算出当前视角下，Y轴的方向
	AddMovementInput(RightVecotor, Value);
}

// Called every frame
void ATgCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATgCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this, &ATgCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATgCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

