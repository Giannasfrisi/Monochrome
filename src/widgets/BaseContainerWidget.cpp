#include "BaseContainerWidget.h"

namespace mc {
    BaseContainerWidget::BaseContainerWidget() {
        appendAllowedEvent("childAdded");
        appendAllowedEvent("childRemoved");
    }

    void BaseContainerWidget::addChild(Shared<BaseWidget> child) {
        CORE_ASSERT((child.get() != this), "Cannot add widget as its own child");
        CORE_ASSERT(!child->getParent(), "Cannot add child, child widget already has a parent");
        CORE_ASSERT(
            !findChild(child->getID()),
            "Cannot add widget, widget with the given UUID already exists"
        );

        d_children.push_back(child);
        child->setParent(this);
        child->forwardEmittedEvent(this, "propertyChanged");
        child->forwardEmittedEvent(this, "requestedFocusGain");
        child->forwardEmittedEvent(this, "requestedFocusLoss");

        fireEvent("childAdded", {
            { "child", child.get() }
        });
    }

    void BaseContainerWidget::insertChild(Shared<BaseWidget> child, uint64_t index) {
        CORE_ASSERT((child.get() != this), "Cannot add widget as its own child");
        CORE_ASSERT(!child->getParent(), "Cannot add child, child widget already has a parent");
        CORE_ASSERT(
            !findChild(child->getID()),
            "Cannot add widget, widget with the given UUID already exists"
        );

        d_children.insert(d_children.begin() + index, child);
        child->setParent(this);
        child->forwardEmittedEvents(this);

        fireEvent("childAdded", {
            { "child", child.get() }
        });
    }

    bool BaseContainerWidget::removeChild(Shared<BaseWidget> child) {
        return removeChild(child->getID());
    }

    bool BaseContainerWidget::removeChild(uuid_t uuid) {
        for (auto it = d_children.begin(); it != d_children.end(); ++it) {
            if (it->get()->getID() == uuid) {
                BaseWidget* widget = it->get();

                // Reset the child's parent
                widget->setParent(nullptr);

                // Erase the child from the list
                d_children.erase(it);

                // Fire the childRemoved event
                fireEvent("childRemoved", {
                    { "child", widget }
                });
                return true;
            }
        }

        return false;
    }

    void BaseContainerWidget::removeAllChildren() {
        while (d_children.size()) {
            auto firstChild = getChild(0);
            removeChild(firstChild);
        }
    }

    Shared<BaseWidget> BaseContainerWidget::findChild(uuid_t uuid) {
        for (auto& widget : d_children) {
            if (widget->getID() == uuid) {
                return widget;
            }
        }

        return nullptr;
    }

    Shared<BaseWidget> BaseContainerWidget::getChild(uint64_t index) {
        return d_children.at(index);
    }
} // namespace mc
