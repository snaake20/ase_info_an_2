-- 1. Printr-un bloc PL/SQL, să se atribuie comision angajaților din departamentul al cărui id este citit de la tastatură. Să se afișeze numărul de modificări totale efectuate.
DECLARE
  v_id_departament ANGAJATI.ID_DEPARTAMENT%TYPE := &id_departament;
BEGIN

UPDATE ANGAJATI SET COMISION=0.1 WHERE ID_DEPARTAMENT = v_id_departament;
IF SQL%FOUND THEN
  DBMS_OUTPUT.PUT_LINE (SQL%ROWCOUNT || ' randuri updatate');
  ROLLBACK;
ELSE
  DBMS_OUTPUT.PUT_LINE('NU s-au produs modificari')
END IF;

END;
/

-- 2. Construiți un bloc PL/SQL prin care să se afișeze informații despre angajații din orașul Toronto.

DECLARE
  cursor cur is SELECT NUME,SALARIUL FROM ANGAJATI ANG, DEPARTAMENTE DEP, LOCATII LOC WHERE ANG.ID_DEPARTAMENT = DEP.ID_DEPARTAMENT AND DEP.ID_LOCATIE = LOC.ID_LOCATIE AND LOC.ORAS = 'Toronto';
  v_nume ANGAJATI.NUME%TYPE;
  v_salariul ANGAJATI.SALARIUL%TYPE;
BEGIN
  OPEN cur;
  LOOP
    EXIT WHEN cur%NOTFOUND;
    FETCH cur INTO v_nume, v_salariul;
    DBMS_OUTPUT.PUT_LINE(v_nume || ' ' || v_salariul);
  END LOOP;
  CLOSE cur;
END;
/

-- 3. Construiți un bloc PL/SQL prin care să se afișeze primele 3 comenzi care au cele mai multe produse comandate.

DECLARE
  cursor cur is SELECT RC.ID_COMANDA, COUNT(DISTINCT RC.ID_PRODUS) FROM RAND_COMENZI RC GROUP BY RC.ID_COMANDA ORDER BY COUNT(DISTINCT RC.ID_PRODUS) DESC FETCH FIRST 3 ROWS ONLY;
  v_id_comanda COMENZI.ID_COMANDA%TYPE;
  v_cantitate RAND_COMENZI.CANTITATE%TYPE;
BEGIN
  OPEN cur;
  LOOP
    FETCH cur INTO v_id_comanda, v_cantitate;
    EXIT WHEN cur%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE(v_id_comanda || ' ' || v_cantitate);
  END LOOP;
  CLOSE cur;
END;
/

-- 4. Construiți un bloc PL/SQL prin care să se afișeze, pentru fiecare departament, valoarea totală a salariilor plătite angajaților.

DECLARE
  cursor cur is SELECT ID_DEPARTAMENT, SUM(SALARIUL * (1 + NVL(COMISION, 0))) FROM ANGAJATI WHERE ID_DEPARTAMENT IS NOT NULL GROUP BY ID_DEPARTAMENT;
  -- variabila compusa v_row cur%ROWTYPE;
  v_id_departament ANGAJATI.ID_DEPARTAMENT%TYPE;
  v_suma_salarii ANGAJATI.SALARIUL%TYPE;
BEGIN
  OPEN cur;
  LOOP
    FETCH cur INTO v_id_departament, v_suma_salarii;
    EXIT WHEN cur%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE(v_id_departament || ' ' || v_suma_salarii);
  END LOOP;
  CLOSE cur;
END;
/

-- 5. Construiți un bloc PL/SQL prin care să se afișeze informații despre angajați, precum și numărul de comenzi intermediate de fiecare.

DECLARE
  cursor cur is SELECT ANG.ID_ANGAJAT, PRENUME, NUME, EMAIL, TELEFON, DATA_ANGAJARE, ID_FUNCTIE, SALARIUL, COMISION, ID_MANAGER, ID_DEPARTAMENT, COUNT(COM.ID_COMANDA) FROM ANGAJATI ANG, COMENZI COM WHERE ANG.ID_ANGAJAT = COM.ID_ANGAJAT GROUP BY ANG.ID_ANGAJAT, PRENUME, NUME, EMAIL, TELEFON, DATA_ANGAJARE, ID_FUNCTIE, SALARIUL, COMISION, ID_MANAGER, ID_DEPARTAMENT;
  v_id_angajat ANGAJATI.ID_ANGAJAT%TYPE;
  v_prenume ANGAJATI.PRENUME%TYPE;
  v_nume ANGAJATI.NUME%TYPE;
  v_email ANGAJATI.EMAIL%TYPE;
  v_telefon ANGAJATI.TELEFON%TYPE;
  v_data_angajare ANGAJATI.DATA_ANGAJARE%TYPE;
  v_id_functie ANGAJATI.ID_FUNCTIE%TYPE;
  v_salariul ANGAJATI.SALARIUL%TYPE;
  v_comision ANGAJATI.COMISION%TYPE;
  v_id_manager ANGAJATI.ID_MANAGER%TYPE;
  v_id_departament ANGAJATI.ID_DEPARTAMENT%TYPE;
  v_nr_comenzi NUMBER;
BEGIN
  OPEN cur;
  LOOP
    FETCH cur INTO v_id_angajat, v_prenume, v_nume, v_email, v_telefon, v_data_angajare, v_id_functie, v_salariul, v_comision, v_id_manager, v_id_departament, v_nr_comenzi;
    EXIT WHEN cur%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE('ID ANGAJAT: ' || v_id_angajat || ', NUME: ' || v_nume || ', SALARIUL: ' || v_salariul || ', Nr. Comenzi: ' || v_nr_comenzi);
  END LOOP;
  CLOSE cur;
END;
/

-- 6. Construiți un bloc PL/SQL prin care să se afișeze pentru fiecare departament (id și nume) informații despre angajații aferenți (id, nume, salariu). Să se afișeze la nivelul fiecărui departament și salariul total plătit. Informațiile vor fi afișate în următoarea manieră:

DECLARE
  v_id_angajat ANGAJATI.ID_ANGAJAT%TYPE;
  v_prenume ANGAJATI.PRENUME%TYPE;
  v_nume ANGAJATI.NUME%TYPE;
  v_email ANGAJATI.EMAIL%TYPE;
  v_telefon ANGAJATI.TELEFON%TYPE;
  v_data_angajare ANGAJATI.DATA_ANGAJARE%TYPE;
  v_id_functie ANGAJATI.ID_FUNCTIE%TYPE;
  v_salariul ANGAJATI.SALARIUL%TYPE;
  v_comision ANGAJATI.COMISION%TYPE;
  v_id_manager ANGAJATI.ID_MANAGER%TYPE;
  v_nr_comenzi NUMBER;
  cursor cur2 is SELECT ANG.ID_DEPARTAMENT, DEP.DENUMIRE_DEPARTAMENT, SUM(SALARIUL * (1 + NVL(COMISION, 0))) FROM ANGAJATI ANG, DEPARTAMENTE DEP  WHERE ANG.ID_DEPARTAMENT IS NOT NULL AND ANG.ID_DEPARTAMENT = DEP.ID_DEPARTAMENT GROUP BY ANG.ID_DEPARTAMENT, DEP.DENUMIRE_DEPARTAMENT;
  -- variabila compusa v_row cur%ROWTYPE;
  v_id_departament ANGAJATI.ID_DEPARTAMENT%TYPE;
  v_denumire_departament DEPARTAMENTE.DENUMIRE_DEPARTAMENT%TYPE;
  v_suma_salarii ANGAJATI.SALARIUL%TYPE;
  cursor cur(departament NUMBER) is SELECT ANG.ID_ANGAJAT, PRENUME, NUME, EMAIL, TELEFON, DATA_ANGAJARE, ID_FUNCTIE, SALARIUL, COMISION, ID_MANAGER FROM ANGAJATI ANG where ANG.ID_DEPARTAMENT = departament;
BEGIN
  OPEN cur2;
  LOOP
    FETCH cur2 INTO v_id_departament, v_denumire_departament, v_suma_salarii;
    EXIT WHEN cur2%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE('*Departament ' || v_denumire_departament);
    OPEN cur(v_id_departament);
      LOOP
        FETCH cur INTO v_id_angajat, v_prenume, v_nume, v_email, v_telefon, v_data_angajare, v_id_functie, v_salariul, v_comision, v_id_manager;
        EXIT WHEN cur%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE('******angajat: ' || v_id_angajat || ', NUME: ' || v_nume || ', SALARIUL: ' || v_salariul * (1+NVL(v_comision, 0)));
      END LOOP;
    CLOSE cur;
    DBMS_OUTPUT.PUT_LINE('Total salarii ' || v_denumire_departament || ': ' || v_suma_salarii);
  END LOOP;
  CLOSE cur2;
END;
/

-- *departament A
-- ******angajat 1
-- ******angajat 2
-- Total salarii A: ...

-- * departament B
-- ******angajat 5
-- ******angajat 6
-- ******angajat 7
-- Total salarii B: ...