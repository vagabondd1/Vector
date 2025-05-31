# 🧮 Класс `Vector` (аналог `std::vector`)

Реализация динамического массива для типа `ValueType` (по умолчанию `double`) с поддержкой базовых операций, итераторов и управления памятью.

---

## 📋 Основные методы

### **Конструкторы и деструктор**
| Метод | Описание |
|-------|----------|
| `Vector()` | Создает пустой вектор. |
| `Vector(const ValueType* array, size_t size, float coef)` | Создает вектор из C-массива. `coef` — коэффициент увеличения емкости. |
| `Vector(const Vector& other)` | Конструктор копирования. |
| `Vector(Vector&& other)` | Конструктор перемещения (переносит ресурсы). |
| `~Vector()` | Освобождает выделенную память. |

### **Операторы присваивания**
| Метод | Описание |
|-------|----------|
| `Vector& operator=(const Vector& other)` | Копирует данные из `other`. |
| `Vector& operator=(Vector&& other)` | Перемещает данные из `other`. |

### **Добавление элементов**
| Метод | Описание |
|-------|----------|
| `void pushBack(const ValueType& value)` | Добавляет элемент в конец. |
| `void pushFront(const ValueType& value)` | Добавляет элемент в начало. |
| `void insert(const ValueType& value, size_t pos)` | Вставляет `value` на позицию `pos`. |
| `void insert(const ValueType* values, size_t size, size_t pos)` | Вставляет массив `values` размера `size` начиная с `pos`. |
| `void insert(const Vector& vector, size_t pos)` | Вставляет содержимое `vector` начиная с `pos`. |

### **Удаление элементов**
| Метод | Описание |
|-------|----------|
| `void popBack()` | Удаляет последний элемент. |
| `void popFront()` | Удаляет первый элемент. |
| `void erase(size_t pos, size_t count = 1)` | Удаляет `count` элементов, начиная с `pos`. |
| `void eraseBetween(size_t beginPos, size_t endPos)` | Удаляет элементы в диапазоне `[beginPos, endPos)`. |