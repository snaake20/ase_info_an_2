-- 1. Creaţi un bloc PL/SQL pentru a selecta codul și data de încheiere a comenzilor încheiate într-un an introdus de la tastatură (prin comandă SELECT simplă, fără să utilizați un cursor explicit).

    -- dacă interogarea returnează mai mult de o valoare pentru codul comenzii, tratați excepția cu o rutină de tratare corespunzătoare și afișați mesajul “Atenţie! In anul yyyy s-au încheiat mai multe comenzi!”;
    -- dacă interogarea nu returnează nicio valoare pentru codul comenzii, tratați excepția cu o rutină de tratare corespunzătoare și afișați mesajul “Atenţie! In anul yyyy nu s-au încheiat comenzi!”;
    -- dacă se returnează o singură linie, afișați codul și data comenzii;
    -- tratați orice altă excepție cu o rutină de tratare corespunzătoare și afișați mesajul “A apărut o altă excepție!”.

--testati cu anul 2015 (o singura comanda) => se face afisarea din zona executabila (comanda SELECT intoarce un singur rezultat)
--testati cu anul 2019 (mai multe comenzi) => SELECT returneaza mai multe linii => TOO_MANY_ROWS
--testati cu anul 2000 (nicio comanda) => SELECT nu returneaza nimic => NO_DATA_FOUND


DECLARE
  v_an NUMBER :=&an;
  v_cod COMENZI.ID_COMANDA%TYPE;
  v_data COMENZI.DATA%TYPE;
  --prea_multe_comenzi exception;
  --pragma exception(prea_multe_comenzi, -01422);
BEGIN
  SELECT ID_COMANDA, DATA INTO v_cod, v_data FROM COMENZI WHERE EXTRACT(YEAR FROM DATA) = v_an;
  DBMS_OUTPUT.PUT_LINE(v_cod || ' ' || v_data);
EXCEPTION
    WHEN NO_DATA_FOUND THEN
    DBMS_OUTPUT.PUT_LINE('Atenţie! In anul ' || v_an || ' nu s-au încheiat comenzi!');
    WHEN TOO_MANY_ROWS THEN
    DBMS_OUTPUT.PUT_LINE('Atenţie! In anul ' || v_an || ' s-au încheiat mai multe comenzi!');
    FOR X IN (
      SELECT ID_COMANDA, DATA FROM COMENZI WHERE EXTRACT(YEAR FROM DATA) = v_an
    )
    LOOP
      DBMS_OUTPUT.PUT_LINE(x.id_comanda || ' ' || x.data);
    END LOOP;
    WHEN OTHERS THEN
    -- DBMS_OUTPUT.PUT_LINE(SQLCODE); --that's how you get the error code
    DBMS_OUTPUT.PUT_LINE('A apărut o altă excepție!');
END;
/


-- 2. Creaţi un bloc PL/SQL prin care se dublează preţul produsului (pret_lista) al cărui cod este citit de la tastatură. În cazul în care acesta nu există (comanda UPDATE nu realizează nicio modificare) se va invoca o excepție. Tratați excepția prin afișarea unui mesaj.

--testati cu id produs 3061 pentru a obtine modificari prin UPDATE => se produce modificarea si se face afisarea din zona executabila
--testati cu id produs 100 pentru a nu obtine modificari prin UPDATE => se invoca exceptia definita de utilizator => se afiseaza mesajul din Exception


DECLARE
  v_cod PRODUSE.ID_PRODUS%TYPE := &cod;
  v_pret PRODUSE.PRET_LISTA%TYPE;
  invalid_prod EXCEPTION;
BEGIN
  SELECT PRET_LISTA INTO v_pret FROM PRODUSE WHERE ID_PRODUS = v_cod;
  DBMS_OUTPUT.PUT_LINE('Before: ' || v_pret);
  UPDATE PRODUSE SET PRET_LISTA = PRET_LISTA * 2 WHERE ID_PRODUS = v_cod RETURNING PRET_LISTA INTO v_pret;
  DBMS_OUTPUT.PUT_LINE('After: ' || v_pret);
  IF SQL%NOTFOUND THEN
    RAISE invalid_prod;
  END IF;
  ROLLBACK;
EXCEPTION
  WHEN invalid_prod THEN
    DBMS_OUTPUT.PUT_LINE('Nu exista produsul!');
END;
/

-- SELECT PRET_LISTA FROM PRODUSE WHERE ID_PRODUS = 3061;

-- 3. Într-un bloc PL/SQL citiți de la tastatură identificatorul unui produs. Afișați denumirea produsului care are acel cod. De asemenea, calculați cantitatea totală comandată din acel produs.

    -- afișați denumirea produsului;
    -- dacă produsul nu există, tratați excepția cu o rutină de tratare corespunzătoare;
    -- dacă produsul nu a fost comandat, invocați o excepție, care se va trata corespunzător;
    -- dacă produsul există și a fost comandat, afișați cantitatea totală comandată;
    -- tratați orice altă excepție cu o rutină de tratare corespunzătoare.

--testati cu id produs 3061 (nu a fost comandat) => se invoca exceptia definita de utilizator => se afiseaza mesajul din Exception
--testati cu id produs 2311 (a fost comandat) => se afiseaza mesajul din zona executabila
--testati cu id produs 100 (nu exista) => NO_DATA_FOUND


DECLARE
  v_cod PRODUSE.ID_PRODUS%TYPE := &cod;
  v_denumire PRODUSE.DENUMIRE_PRODUS%TYPE;
  v_check NUMBER;
  nu_a_fost_comandat EXCEPTION;
  v_cantitate NUMBER;
BEGIN
  SELECT PR.DENUMIRE_PRODUS INTO v_denumire FROM PRODUSE PR WHERE PR.ID_PRODUS = v_cod;
  DBMS_OUTPUT.PUT_LINE('Denumire produs: ' || v_denumire);
  SELECT COUNT(PR.ID_PRODUS) INTO v_check FROM PRODUSE PR, RAND_COMENZI RC WHERE PR.ID_PRODUS = v_cod AND PR.ID_PRODUS = RC.ID_PRODUS;
  IF v_check = 0 THEN
  RAISE nu_a_fost_comandat;
  END IF;
  SELECT SUM(RC.CANTITATE) INTO v_cantitate FROM PRODUSE PR, RAND_COMENZI RC WHERE PR.ID_PRODUS = v_cod AND PR.ID_PRODUS = RC.ID_PRODUS;
  DBMS_OUTPUT.PUT_LINE('Cantitate totala comandata: ' || v_cantitate);
EXCEPTION
  WHEN NO_DATA_FOUND THEN
    DBMS_OUTPUT.PUT_LINE('Produsul cu codul: ' || v_cod || ' nu exista!');
  WHEN nu_a_fost_comandat THEN
    DBMS_OUTPUT.PUT_LINE('Produsul cu codul: ' || v_cod || ' nu a fost comandat!');
END;
/


-- 4. Într-un bloc PL/SQL utilizați un cursor parametrizat pentru a prelua numele, salariul și vechimea angajaților dintr-un departament furnizat drept parametru.

--     deschideți cursorul prin indicarea ca parametru a unei variabile de substituție, a cărei valoare să fie citită de la tastatură;
--     parcurgeți cursorul și afișați informațiile solicitate pentru acei angajați care fac parte din departamentul indicat;
--     afișați numărul total de angajați parcurși;
--     în cazul în care nu există departamentul indicat, se va invoca o excepție, care se va trata corespunzător;
--     în cazul în care nu există angajați în departamentul indicat, se va invoca o excepție, care se va trata corespunzător.

--testati cu id departament 7 pentru a verifica lipsa departamentului  => se invocă excepție
--testati cu id departament 210 pentru a nu obtine niciun rezultat  => SELECT nu returneaza nimic, deci cursorul indica o zona goala de memorie => nu se face nicio parcurgere
--testati cu id departament 50 pentru a obtine mai multe rezultate => se efectueaza parcurgerile asupra setului de date adus in memorie


DECLARE
  v_department_exists NUMBER;
  v_nr_angajati NUMBER;
  v_nume ANGAJATI.NUME%TYPE;
  v_salariul ANGAJATI.SALARIUL%TYPE;
  v_vechime NUMBER;
  v_id_dep ANGAJATI.ID_DEPARTAMENT%TYPE  := &id_dep;
  CURSOR CUR IS SELECT NUME, SALARIUL, ROUND((SYSDATE - DATA_ANGAJARE)/365) VECHIME FROM ANGAJATI WHERE ID_DEPARTAMENT = v_id_dep;
  no_angajati EXCEPTION;
  no_department EXCEPTION;
BEGIN
  -- throw exception if department doesn't exist
  SELECT COUNT(ID_DEPARTAMENT) INTO v_department_exists FROM DEPARTAMENTE WHERE ID_DEPARTAMENT = v_id_dep;
  IF v_department_exists = 0 THEN
  RAISE no_department;
  END IF;
  SELECT COUNT(ID_ANGAJAT) INTO v_nr_angajati FROM ANGAJATI WHERE ID_DEPARTAMENT = v_id_dep;
  IF v_nr_angajati = 0 THEN
  RAISE no_angajati;
  END IF;
  OPEN CUR;
  LOOP
  EXIT WHEN CUR%NOTFOUND;
  FETCH CUR INTO v_nume, v_salariul, v_vechime;
  DBMS_OUTPUT.PUT_LINE('Nume: ' || v_nume || ' Salariul: ' || v_salariul || ' Vechime: ' || v_vechime);
  END LOOP;
  CLOSE CUR;
  DBMS_OUTPUT.PUT_LINE('Nr angajati: ' || v_nr_angajati);
EXCEPTION
  WHEN no_department THEN
    DBMS_OUTPUT.PUT_LINE('Nu exista departamentul cu id-ul ' || v_id_dep);
  WHEN no_angajati THEN
    DBMS_OUTPUT.PUT_LINE('Nu exista angajati in departamentul ' || v_id_dep);
  WHEN OTHERS THEN
    DBMS_OUTPUT.PUT_LINE(SQLCODE);
END;
/