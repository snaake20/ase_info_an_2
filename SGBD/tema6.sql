-- 1. Sa se creeze o functie PL/SQL care sa returneze valoarea comenzilor date de clientul indicat drept parametru. Tratati eventualele exceptii.

CREATE OR REPLACE FUNCTION valoare_comenzi_nume_client (nume IN CLIENTI.NUME_CLIENT%TYPE) RETURN NUMBER IS
  valoare NUMBER;
BEGIN
  SELECT SUM(RAND_COMENZI.CANTITATE * RAND_COMENZI.PRET) INTO valoare
  FROM COMENZI, RAND_COMENZI, CLIENTI
  WHERE COMENZI.ID_COMANDA = RAND_COMENZI.ID_COMANDA AND COMENZI.ID_CLIENT = CLIENTI.ID_CLIENT AND CLIENTI.NUME_CLIENT = nume;
  RETURN valoare;
EXCEPTION
  WHEN NO_DATA_FOUND THEN
    DBMS_OUTPUT.PUT_LINE('Nu exista comenzi pentru clientul ' || nume);
    RETURN 0;
END;
/

-- SELECT SUM(RAND_COMENZI.CANTITATE * RAND_COMENZI.PRET) FROM COMENZI, RAND_COMENZI, CLIENTI WHERE COMENZI.ID_COMANDA = RAND_COMENZI.ID_COMANDA AND COMENZI.ID_CLIENT = CLIENTI.ID_CLIENT AND CLIENTI.NUME_CLIENT = 'Welles';

-- SELECT NUME_CLIENT FROM CLIENTI;

BEGIN
  DBMS_OUTPUT.PUT_LINE( 'Valoare: ' ||valoare_comenzi_nume_client('Welles'));
END;
/
-- 2. Sa se creeze o procedura PL/SQL care sa afiseze topul primilor n clienti (identificati prin nume_client) ordonati descrescator in functie de valoarea comenzilor proprii si procentul detinut de acestia din valoarea totala a vanzarilor. n este indicat drept parametru.

-- SELECT NUME_CLIENT FROM CLIENTI WHERE NUME_CLIENT = 'Roberts'; -- sunt duplicate

CREATE OR REPLACE PROCEDURE Top_n_clienti(n IN NUMBER) IS
  CURSOR c1 IS
    SELECT NUME_CLIENT, valoare_comenzi_nume_client(NUME_CLIENT) VALOARE_COMANDA
    FROM CLIENTI
    WHERE valoare_comenzi_nume_client(NUME_CLIENT) IS NOT NULL
    ORDER BY VALOARE_COMANDA DESC;
  v_nume_client CLIENTI.NUME_CLIENT%TYPE;
  v_valoare NUMBER;
  v_total NUMBER;
  v_nr NUMBER := 0;
BEGIN
  SELECT SUM(RAND_COMENZI.CANTITATE * RAND_COMENZI.PRET) INTO v_total
  FROM COMENZI, RAND_COMENZI
  WHERE COMENZI.ID_COMANDA = RAND_COMENZI.ID_COMANDA;
  OPEN c1;
  LOOP
    FETCH c1 INTO v_nume_client, v_valoare;
    EXIT WHEN c1%NOTFOUND OR v_nr = n;
    DBMS_OUTPUT.PUT_LINE(v_nume_client || ' ' || v_valoare || ' ' || ROUND(v_valoare / v_total * 100, 2) || '%');
    v_nr := v_nr + 1;
  END LOOP;
  CLOSE c1;
END;
/
-- apel

BEGIN
  Top_n_clienti(5);
END;
/
-- 3. Sa se construiasca un bloc PL/SQL prin care sa se calculeze si sa se memoreze intr-o tabela indexata: pentru fiecare client (nume_client) valoarea totala a comenzilor efectuate.

-- investigate bulk collect into collection after fetching from cursor

CREATE OR REPLACE PROCEDURE valoare_comenzi_clienti IS -- vor lipsi duplicatele
  TYPE VALOARE_COMENZI_RECORD IS RECORD (
    NUME CLIENTI.NUME_CLIENT%TYPE,
    VALOARE NUMBER
  );
  r VALOARE_COMENZI_RECORD;
  TYPE VALOARE_COMENZI_CLIENTI IS TABLE OF VALOARE_COMENZI_RECORD INDEX BY PLS_INTEGER;
  VALOAREA_COMENZI_CLIENTI VALOARE_COMENZI_CLIENTI;
  CURSOR c1 IS
    SELECT NUME_CLIENT, valoare_comenzi_nume_client(NUME_CLIENT) VALOARE_COMANDA
    FROM CLIENTI
    WHERE valoare_comenzi_nume_client(NUME_CLIENT) IS NOT NULL
    ORDER BY VALOARE_COMANDA DESC;
  v_nume_client CLIENTI.NUME_CLIENT%TYPE;
  v_valoare NUMBER;
  v_nr_de_intrari PLS_INTEGER:=0;
  v_index PLS_INTEGER :=0;
BEGIN
  OPEN c1;
  LOOP
    FETCH c1 INTO r;
    EXIT WHEN c1%NOTFOUND;
    VALOAREA_COMENZI_CLIENTI(v_index) := r;
    v_index := v_index + 1;
  END LOOP;
  CLOSE c1;
  DBMS_OUTPUT.PUT_LINE('Numarul de intrari: ' || VALOAREA_COMENZI_CLIENTI.COUNT);
  WHILE v_nr_de_intrari < VALOAREA_COMENZI_CLIENTI.COUNT LOOP
    DBMS_OUTPUT.PUT_LINE(VALOAREA_COMENZI_CLIENTI(v_nr_de_intrari).nume || ' ' || VALOAREA_COMENZI_CLIENTI(v_nr_de_intrari).valoare);
    v_nr_de_intrari := v_nr_de_intrari + 1;
  END LOOP;
END;
/

-- Sa se afiseze si numarul de elemente ale colectiei, dar si valorile elementelor acesteia.

BEGIN
  valoare_comenzi_clienti;
END;
/

--😥😥😥

CREATE OR REPLACE PROCEDURE valoare_comenzi_clienti IS -- better
  TYPE VALOARE_COMENZI_RECORD IS RECORD (
    NUME CLIENTI.NUME_CLIENT%TYPE,
    VALOARE NUMBER
  );
  r VALOARE_COMENZI_RECORD;
  TYPE VALOARE_COMENZI_CLIENTI IS TABLE OF VALOARE_COMENZI_RECORD INDEX BY PLS_INTEGER;
  VALOAREA_COMENZI_CLIENTI VALOARE_COMENZI_CLIENTI;
BEGIN
  SELECT NUME_CLIENT, valoare_comenzi_nume_client(NUME_CLIENT) VALOARE_COMANDA BULK COLLECT INTO VALOAREA_COMENZI_CLIENTI
    FROM CLIENTI
    WHERE valoare_comenzi_nume_client(NUME_CLIENT) IS NOT NULL
    ORDER BY VALOARE_COMANDA DESC;
  DBMS_OUTPUT.PUT_LINE('Numarul de intrari: ' || VALOAREA_COMENZI_CLIENTI.COUNT);
  FOR r in VALOAREA_COMENZI_CLIENTI.FIRST .. VALOAREA_COMENZI_CLIENTI.LAST LOOP
    DBMS_OUTPUT.PUT_LINE(VALOAREA_COMENZI_CLIENTI(r).nume || ' ' || VALOAREA_COMENZI_CLIENTI(r).valoare);
  END LOOP;
END;
/