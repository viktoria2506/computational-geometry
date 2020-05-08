# computational-geometry
## C. Rendezvous
Даны N точек. Найдите 2 из них, такие, что расстояние между ними минимально.
#### Формат ввода
Первая строка входного файла содержит целое число N () — количество точек. Каждая из следующих N строк содержит пару целых чисел X и Y, разделённых пробелом, — координаты (). Все точки различны.
#### Формат вывода
Единственная строка выходного файла должна содержать координаты двух выбранных точек.
## E. Hull
Дано N точек на плоскости.
Нужно построить их выпуклую оболочку.
Гарантируется, что выпуклая оболочка не вырождена.
#### Формат ввода
В первой строке число N (3 ≤ N ≤ 10^5). Следующие N строк содержат пары целых чисел x и y (-10^9 ≤ x,y ≤ 10^9) — точки.
Точки произвольны. Бывают совпадающие, бывают лежащие на одной прямой в большом количестве.
#### Формат вывода
В первой строке выведите N — число вершин выпуклой оболочки. Следующие N строк должны содержать координаты вершин в порядке обхода. Никакие три подряд идущие точки не должны лежать на одной прямой.
