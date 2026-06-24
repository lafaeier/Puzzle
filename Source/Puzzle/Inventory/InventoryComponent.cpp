#include "InventoryComponent.h"

void UInventoryComponent::AddItem(FName ItemID)
{
	Items.AddUnique(ItemID);
}

void UInventoryComponent::RemoveItem(FName ItemID)
{
	Items.Remove(ItemID);
}

bool UInventoryComponent::HasItem(FName ItemID) const
{
	return Items.Contains(ItemID);
}
