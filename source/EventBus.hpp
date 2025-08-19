#pragma once

#include <functional>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <memory>
#include <algorithm>

namespace Hijinks {
   // A simple, header-only, type-safe event bus with queued delivery.
   class EventBus {
   public:
      using SubscriptionId = std::size_t;

      EventBus() = default;
      ~EventBus() = default;

      EventBus(const EventBus&) = delete;
      EventBus& operator=(const EventBus&) = delete;
      EventBus(EventBus&&) noexcept = default;
      EventBus& operator=(EventBus&&) noexcept = default;

      // Subscribe a handler for event type E. Returns a token for (optional) unsubscription.
      template<class E>
      SubscriptionId Subscribe(std::function<void(const E&)> fn) {
         auto& list = subscriptions<E>();
         const SubscriptionId id = next_id_++;
         list.emplace_back(id, std::move(fn));
         return id;
      }

      // Unsubscribe by id for event type E (no-op if not found).
      template<class E>
      void Unsubscribe(SubscriptionId id) {
         auto& list = subscriptions<E>();
         list.erase(std::remove_if(list.begin(), list.end(), [id](const auto& p)
            { return p.first == id; }),
            list.end());
      }

      // Queue an event for later delivery (during DispatchPending).
      template<class E>
      void Publish(const E& e) {
         queue_.emplace_back([this, e]() { Deliver(e); });
      }

      // Deliver immediately (synchronous).
      template<class E>
      void PublishImmediate(const E& e) {
         Deliver(e);
      }

      // Deliver all queued events and clear the queue.
      void DispatchPending() {
         // move out to avoid re-entrancy issues if handlers publish more events
         auto pending = std::move(queue_);
         queue_.clear();
         for (auto& thunk : pending)
            thunk();
      }

   private:
      struct SubscriptionBase {
         virtual ~SubscriptionBase() = default;
      };

      template<class E>
      struct Subscriptions : SubscriptionBase {
         std::vector<std::pair<SubscriptionId, std::function<void(const E&)>>> fns;
      };

      template<class E>
      std::vector<std::pair<SubscriptionId, std::function<void(const E&)>>>& subscriptions() {
         auto key = std::type_index(typeid(E));
         auto it = map_.find(key);
         if (it == map_.end()) {
            auto ins = map_.emplace(key, std::make_unique<Subscriptions<E>>());
            it = ins.first;
         }
         return static_cast<Subscriptions<E>*>(it->second.get())->fns;
      }

      template<class E>
      void Deliver(const E& e) {
         auto key = std::type_index(typeid(E));
         auto it = map_.find(key);
         if (it == map_.end()) return;
         auto* list = static_cast<Subscriptions<E>*>(it->second.get());
         // Call each subscriber
         for (auto& pair : list->fns) {
            pair.second(e);
         }
      }

      std::unordered_map<std::type_index, std::unique_ptr<SubscriptionBase>> map_;
      std::vector<std::function<void()>> queue_;
      SubscriptionId next_id_ = 1;
   };
}
