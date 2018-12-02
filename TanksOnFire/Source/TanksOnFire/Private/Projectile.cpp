// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	AttachementsForProjectile();
}

void AProjectile::AttachementsForProjectile()
{
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	//CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->SetupAttachment(CollisionMesh);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->SetupAttachment(CollisionMesh);
	ImpactBlast->bAutoActivate = false;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement component"));
	// false is not to make the projectile component file, unless fired
	ProjectileMovementComponent->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->SetupAttachment(CollisionMesh);
}

void AProjectile::LaunchProjectile(float launchSpeed)
{
	float time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f: Projectile fires at %f"), time, launchSpeed);
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * launchSpeed);
	// activates the behavior that we have stopped in constructor and re-initiating again, so it would pick the speed
	ProjectileMovementComponent->Activate();
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::ShowImpactWithParticleEffect()
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	// impulse is integral of force over time (J = average force F over delta time T)
	ExplosionForce->FireImpulse();
	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	// this would call, all the actors that implemented TakeDamage method
	UGameplayStatics::ApplyRadialDamage(this, DamageRate, GetActorLocation(), ExplosionForce->Radius, UDamageType::StaticClass(), TArray<AActor*>());
	/*FTimerHandle outTimer;
	GetWorld()->GetTimerManager().SetTimer(outTimer, this, &AProjectile::OnTimeExpire, DestoryDelay);*/
}

void AProjectile::OnTimeExpire()
{
	Destroy();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

