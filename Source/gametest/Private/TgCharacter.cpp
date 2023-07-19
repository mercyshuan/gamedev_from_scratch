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
	SpringArmComp->bUsePawnControlRotation = true; //�����ɱ۵�ʹ��pawn��ת ѡ���
	SpringArmComp->SetupAttachment(RootComponent); //�����ɱ۰󶨵���������
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp); //������󶨵����ɱ���

	GetCharacterMovement()->bOrientRotationToMovement = true;  // pawn����������ڳ����ӽǷ��� 
	bUseControllerRotationYaw = false;//�������ӽ���תѡ�� �ر�
}

// Called when the game starts or when spawned
void ATgCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATgCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();//����һ����ת�����ɻ���ӽǷ���
	ControlRot.Pitch = 0.0f;//����pitch��roll��ֵ
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), Value); //�������������ƶ���ɫ��ControlRot.Vector() ��ȡ��ת���ķ���
}



void ATgCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();//����һ����ת�����ɻ���ӽǷ���
	ControlRot.Pitch = 0.0f;//����pitch��roll��ֵ
	ControlRot.Roll = 0.0f;
	FVector RightVecotor = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y); 
	//FRotationMatrix��ĳ����תת��Ϊ��ת���󣬳��������ᣬ���ɼ������ǰ�ӽ��£�Y��ķ���
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

