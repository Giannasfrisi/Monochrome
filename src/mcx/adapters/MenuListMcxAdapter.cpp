#include "MenuListMcxAdapter.h"
#include <widgets/MenuList.h>
#include <mcx/McxEngine.h>

namespace mc::mcx {
    Shared<BaseWidget> MenuListMcxAdapter::createWidgetInstance() {
        return MakeRef<MenuList>();
    }

    void MenuListMcxAdapter::applyProperties(
        Shared<BaseWidget>& widget,
        Shared<McxNode>& mcxNode
    ) {
        // Handle child mcx nodes manually as items to add
        mcxNode->childrenHandled = true;

        auto menuList = std::static_pointer_cast<MenuList>(widget);
        menuList->name =
            mcxNode->getAttribute("name", menuList->name);

        menuList->borderColor =
            mcxNode->getColorAttribute("borderColor", menuList->borderColor);

        menuList->itemTextColor =
            mcxNode->getColorAttribute("itemTextColor", menuList->itemTextColor);

        menuList->itemBackgroundColor =
            mcxNode->getColorAttribute("itemBackgroundColor", menuList->itemBackgroundColor);

        menuList->borderThickness =
            mcxNode->getUIntAttribute("norderThickness", menuList->borderThickness);

        menuList->itemSize =
            mcxNode->getUIntAttribute("itemSize", menuList->itemSize);

        auto spawnDirection = mcxNode->getAttribute("spawnDirection", "right");
        if (spawnDirection == "left") {
            menuList->spawnDirection = OverflowDirection::Left;
        } else if (spawnDirection == "right") {
            menuList->spawnDirection = OverflowDirection::Right;
        } else if (spawnDirection == "up") {
            menuList->spawnDirection = OverflowDirection::Up;
        } else if (spawnDirection == "down") {
            menuList->spawnDirection = OverflowDirection::Down;
        }

        // Handle child nodes as items to be added
        for (auto& childNode : mcxNode->getChildren()) {
            auto nodeType = childNode->getType();

            // Sanity checking the node type
            if (nodeType != "item" && nodeType != "MenuList") {
                printf("Error parsing MenuList child node,"
                       "type has to be either <item> or <MenuList>\n");
                continue;
            }

            if (nodeType == "item") {
                // Making sure the node has a value attribute
                if (!childNode->hasAttribute("value")) {
                    printf("Error parsing MenuList item node: expected <item value=\"...\"/>\n");
                    continue;
                }

                auto menuItem = childNode->getAttribute("value");
                menuList->addMenuItem(menuItem);
            } else {
                // Parse the submenu MenuList node
                auto submenu = std::static_pointer_cast<MenuList>(
                    McxEngine::parseWidget(childNode)
                );

                menuList->addSubMenu(submenu);
            }
        }
    }
} //namespace mc::mcx
