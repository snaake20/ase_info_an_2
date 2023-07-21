CREATE OR REPLACE PROCEDURE rezolvareEcuatieDeGr2(a NUMBER, b NUMBER, c NUMBER) 
IS
  delta NUMBER := b*b - 4*a*c;
  radacina1 NUMBER;
  radacina2 NUMBER;
BEGIN
  IF delta < 0 THEN
    DBMS_OUTPUT.PUT_LINE('Ecuatia nu are radacini reale');
  ELSIF delta = 0 THEN
    radacina1 := -b / (2*a);
    DBMS_OUTPUT.PUT_LINE('Ecuatia are radacini egale: ' || radacina1);
  ELSE
    radacina1 := (-b + sqrt(delta)) / (2*a);
    radacina2 := (-b - sqrt(delta)) / (2*a);
    DBMS_OUTPUT.PUT_LINE('Ecuatia are doua radacini: ' || radacina1 || ' si ' || radacina2);
  END IF;
END;
/
-- test apel
BEGIN
  rezolvareEcuatieDeGr2(1, -5, 6);
END;
/