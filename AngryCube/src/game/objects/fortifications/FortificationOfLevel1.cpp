#include "pch.h"
#include "FortificationOfLevel1.h"

#include "game/objects/fortifications/Brick.h"


FortificationOfLevel1::FortificationOfLevel1(Scene* parentScene)
    : Fortification(parentScene)
{
    auto brickTemplate = std::make_shared<Brick>(parentScene, 5.0f);
    float scale = 0.5f;
    brickTemplate->GetTransform().SetScale(glm::vec2(scale, scale));
    brickTemplate->GetPhysics().Disable();
    brickTemplate->GetCollision().Enable();

    float padding = 2.0f;

    auto brickLowest = brickTemplate->Clone();
    brickLowest->GetTransform().SetTranslation(glm::vec2(0.0f, brickLowest->GetCollisionMesh()->GetHeight() / 2.0f));
    AttachChild(brickLowest, false);

    auto brickMiddle = brickTemplate->Clone();
    brickMiddle->GetTransform().SetTranslation(brickLowest->GetTransform().GetTranslation() +
        glm::vec2(0.0f, brickMiddle->GetCollisionMesh()->GetHeight() + padding));
    AttachChild(brickMiddle, false);

    auto brickHigh = brickTemplate->Clone();
    brickHigh->GetTransform().SetTranslation(brickMiddle->GetTransform().GetTranslation() +
        glm::vec2(0.0f, brickHigh->GetCollisionMesh()->GetHeight() + padding));
    AttachChild(brickHigh, false);
}

std::shared_ptr<GameObject> FortificationOfLevel1::Clone() const
{
    return std::make_shared<FortificationOfLevel1>(*this);
}

std::shared_ptr<GameObject> FortificationOfLevel1::MoveClone()
{
    return std::make_shared<FortificationOfLevel1>(std::move(*this));
}
