--1. Creati procedura Top_5_angajati prin care sa afisati informatii despre primii 5 salariati angajati (se va realiza sortarea în functie de câmpul Data_Angajare). Apelati procedura.

CREATE OR REPLACE PROCEDURE Top_5_angajati AS
  CURSOR TOP_5_ANGAJATI IS SELECT * FROM Angajati ORDER BY Data_Angajare FETCH FIRST 5 ROWS ONLY;
  angajat ANGAJATI%ROWTYPE;
BEGIN
  OPEN TOP_5_ANGAJATI;
  LOOP
    FETCH TOP_5_ANGAJATI INTO angajat;
    EXIT WHEN TOP_5_ANGAJATI%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE('Nume: ' || angajat.Nume || ' Prenume: ' || angajat.Prenume || ' Data angajarii: ' || angajat.Data_Angajare || ' Salariu: ' || angajat.Salariul);
  END LOOP;
  CLOSE TOP_5_ANGAJATI;
END;
/

-- Apelare

BEGIN
  Top_5_angajati;
END;
/

--2. Construiti procedura Valoare_comenzi care sa calculeze si sa afiseze valoarea fiecarei comenzi încheiate într-un an indicat ca parametru de intrare. Tratați printr-o excepție cazul în care nu există comenzi plasate în anul indicat. Apelati procedura.

CREATE OR REPLACE PROCEDURE valoare_comenzi_in_anul (an_comanda IN NUMBER) IS
  CURSOR COMENZI_AN IS SELECT COMENZI.ID_COMANDA, SUM(RAND_COMENZI.CANTITATE * RAND_COMENZI.PRET) valoare_comanda FROM Comenzi, RAND_COMENZI WHERE EXTRACT(YEAR FROM Data) = an_comanda AND COMENZI.ID_COMANDA = RAND_COMENZI.ID_COMANDA GROUP BY COMENZI.ID_COMANDA;
  comanda COMENZI.ID_COMANDA%TYPE;
  valoare NUMBER;
BEGIN
  OPEN COMENZI_AN;
  LOOP
    FETCH COMENZI_AN INTO comanda, valoare;
    EXIT WHEN COMENZI_AN%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE('Comanda cu ID-ul ' || comanda || ' are valoarea ' || valoare);
  END LOOP;
  CLOSE COMENZI_AN;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
      DBMS_OUTPUT.PUT_LINE('Nu exista comenzi in anul ' || an_comanda);
END;
/

-- Apelare

BEGIN
  valoare_comenzi_in_anul(2019);
END;
/

--3. Construiti functia Calcul_vechime care sa returneze vechimea angajatului al carui id este dat ca parametru de intrare. Tratati printr-o excepție cazul în care angajatul indicat nu există.

CREATE OR REPLACE FUNCTION Calcul_vechime (p_id IN ANGAJATI.ID_ANGAJAT%TYPE) RETURN NUMBER IS
  vechime NUMBER;
BEGIN
  SELECT ROUND((SYSDATE - DATA_ANGAJARE) / 365) vechime_angajat INTO vechime FROM Angajati WHERE ID_ANGAJAT = p_id;
  RETURN vechime;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
      DBMS_OUTPUT.PUT_LINE('Nu exista angajat cu ID-ul ' || p_id);
END;
/

-- Apelare

BEGIN
  DBMS_OUTPUT.PUT_LINE('Vechimea angajatului cu ID-ul 1 este ' || Calcul_vechime(100));
END;
/

--4. Apelati functia de mai sus în cadrul unei proceduri, Vechime_angajati, prin care se vor parcurge toti angajatii, în scopul afisarii vechimii fiecaruia.

CREATE OR REPLACE PROCEDURE Vechime_angajati AS
  CURSOR ANGAJATI IS SELECT * FROM Angajati;
  angajat ANGAJATI%ROWTYPE;
BEGIN
  OPEN ANGAJATI;
  LOOP
    FETCH ANGAJATI INTO angajat;
    EXIT WHEN ANGAJATI%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE('Nume: ' || angajat.Nume || ' Prenume: ' || angajat.Prenume || ' Vechime: ' || Calcul_vechime(angajat.ID_ANGAJAT));
  END LOOP;
  CLOSE ANGAJATI;
END;
/

-- Apelare

BEGIN
  Vechime_angajati;
END;