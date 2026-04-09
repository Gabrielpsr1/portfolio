# 🚦 Traffic — CS50 AI

A development log documenting the process of building a 
Convolutional Neural Network (CNN) to classify traffic signs
from the GTSRB dataset.

---

## 🧠 The Process

Building this CNN was a journey of trial and error. Each attempt
taught me something new about how architecture choices affect
a model's ability to learn.

---

### Attempt 1 — The Starting Point

My first model was simple: one convolutional layer, one hidden layer.

| Parameter       | Value   |
|----------------|---------|
| Filters         | 32      |
| Kernel size     | (3, 3)  |
| Pool size       | (2, 2)  |
| Hidden units    | 128     |
| Dropout         | 0.5     |

**Result:** `accuracy: 0.0551 — loss: 3.5058` ❌

Essentially random guessing. The model wasn't learning anything.
My plan: add more filters and more hidden layers, keeping the
pool size and kernel unchanged.

---

### Attempt 2 — More Filters, More Units

I increased the filters and doubled the hidden layer units,
hoping for improvement.

| Parameter       | Value   |
|----------------|---------|
| Filters         | 48      |
| Hidden units    | 256     |

**Result:** `accuracy: 0.0536 — loss: 3.5067` ❌

No meaningful progress. Simply scaling up the same architecture
wasn't the answer. I decided to go deeper with more convolutional
layers, and brought the hidden units back to 128.

---

### Attempt 3 — Going Deeper 🔑

This was the turning point. Instead of one convolutional layer,
I stacked three — each doubling the filters to compensate for
the information lost in pooling: `32 → 64 → 128`.
I also added three hidden layers of 128 units each.

**Result:** `accuracy: 0.6202 — loss: 1.0348` ✅

A massive jump. Depth was clearly the missing ingredient.

---

### Attempt 4 — Best Model 🏆

I pushed further: four convolutional layers, four hidden layers,
doubling the units at each dense layer.

**Result:** `accuracy: 0.8513 — loss: 0.4270` ✅✅

Great results. The architecture had reached the pooling limit,
so adding more convolutional layers wasn't viable anymore.

---

### Attempts 5, 6 & 7 — Diminishing Returns

I experimented with more hidden layers and more filters,
but the results got worse:

| Attempt | Accuracy | Loss   |
|---------|----------|--------|
| 5       | 0.3850   | 1.7613 |
| 6       | 0.5956   | 1.1588 |
| 7       | 0.3857   | 1.8663 |

Overfitting and instability. More complexity wasn't helping.

---

### Final Model — Fine-tuning 🎯

I returned to Attempt 4's architecture and made one small
adjustment: lowering the dropout from `0.5` to `0.4`.

**Result:** `accuracy: 0.9267 — loss: 0.2678` 🏅

The best result of all. Sometimes less regularization is
exactly what the model needs.

---

## 💡 Key Takeaways

- **Depth beats width** — stacking convolutional layers matters
  more than just increasing filters or units.
- **Doubling filters across layers** compensates for spatial
  information lost in pooling.
- **Fine-tuning small parameters** like dropout can make a
  significant difference at the end.
- More complexity doesn't always mean better results —
  knowing when to stop is part of the process.
