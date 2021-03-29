# RandCircleAreaCalculator

A Monte Carlo calculator for pi. Generates random coordinates in quadrants I and II and sees if they fall within 1 unit of (0, 0).
The amount that fall within 1 unit are counted in a parallelized `for` loop, and pi is calculated with `hits / throws`.
