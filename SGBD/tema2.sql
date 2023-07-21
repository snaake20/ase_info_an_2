--1. Într-un bloc PL/SQL să se modifice salariul angajatului citit de la tastatură în funcție de numărul de comenzi pe care acesta le-a intermediat. Urmați pașii:
  --  inițial, se vor afișa numele și salariul angajatului citit de la tastatură
  --  se va calcula și se va afișa numărul de comenzi intermediate de angajatul respectiv
  --  în cazul în care acesta este între 3 și 7, salariul angajatului va crește cu 10%
  --  în cazul în care acesta este mai mare decât 7, salariul angajatului va crește cu 20%
  --  altfel, salariul angajatului rămâne nemodificat
  --  se va opera modificarea salariului la nivelul tabelei
  --  la final, se va afișa salariul nou al angajatului respectiv

DECLARE
  v_id ANGAJATI.ID_ANGAJAT%TYPE := &id_angajat;
  v_nume ANGAJATI.NUME%TYPE;
  v_salariu ANGAJATI.SALARIUL%TYPE;
  v_nr_comenzi NUMBER;
BEGIN
  SELECT NUME, SALARIUL INTO v_nume, v_salariu FROM ANGAJATI WHERE ID_ANGAJAT=v_id;
  DBMS_OUTPUT.PUT_LINE('Nume: ' || v_nume || ' Salariul: ' || v_salariu);
  SELECT COUNT(ID_COMANDA) INTO v_nr_comenzi FROM COMENZI WHERE ID_ANGAJAT = v_id;
  DBMS_OUTPUT.PUT_LINE('Nr comenzi: ' || v_nr_comenzi);
  CASE
  WHEN v_nr_comenzi BETWEEN 3 AND 7 THEN v_salariu:=v_salariu*1.1;
  WHEN v_nr_comenzi > 7 THEN v_salariu:=v_salariu*1.2;
  END CASE;
  --here update
  UPDATE ANGAJATI SET SALARIUL=v_salariu WHERE ID_ANGAJAT=v_id RETURNING SALARIUL INTO v_salariu;
  DBMS_OUTPUT.PUT_LINE('Salariul after update: ' || v_salariu);
END;
/

--2. Într-un bloc PL/SQL să se parcurgă toți angajații cu id_angajat de la 100 la 120, afișând numele, salariul și vechimea.
 
DECLARE
  v_nume ANGAJATI.NUME%TYPE;
  v_salariu ANGAJATI.SALARIUL%TYPE;
  v_vechime NUMBER;
BEGIN
  FOR IDX IN 100..120
    LOOP
      SELECT NUME, SALARIUL, ROUND((SYSDATE - DATA_ANGAJARE)/365) INTO v_nume, v_salariu, v_vechime FROM ANGAJATI WHERE ID_ANGAJAT=IDX;
      DBMS_OUTPUT.PUT_LINE('INDEX: ' || IDX || ', NUME: ' || v_nume || ', SALARIUL: ' || v_salariu || ', VECHIME: ' || v_vechime);
    END LOOP;
END;
/
--3. Într-un bloc PL/SQL să se parcurgă toți angajații, folosind pe rând structurile: FOR-LOOP, WHILE-LOOP, LOOP-EXIT WHEN
 
DECLARE
  v_min_ang NUMBER;
  v_max_ang NUMBER;
  v_idx NUMBER;
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
  v_verif NUMBER;
BEGIN
  SELECT MIN(ID_ANGAJAT), MAX(ID_ANGAJAT) INTO v_min_ang, v_max_ang FROM ANGAJATI;
  DBMS_OUTPUT.PUT_LINE('FOR: ');
  FOR IDX IN v_min_ang..v_max_ang LOOP
    SELECT COUNT(ID_ANGAJAT) INTO v_verif FROM ANGAJATI WHERE ID_ANGAJAT=IDX;
    if v_verif = 1 then
      SELECT ID_ANGAJAT, PRENUME, NUME, EMAIL, TELEFON, DATA_ANGAJARE, ID_FUNCTIE, SALARIUL, COMISION, ID_MANAGER, ID_DEPARTAMENT INTO v_id_angajat, v_prenume, v_nume, v_email, v_telefon, v_data_angajare, v_id_functie, v_salariul, v_comision, v_id_manager, v_id_departament FROM ANGAJATI WHERE ID_ANGAJAT=IDX;
      DBMS_OUTPUT.PUT_LINE('ID ANGAJAT: ' || v_id_angajat || ', NUME: ' || v_nume || ', SALARIUL: ' || v_salariul);
    end if;
  END LOOP;
  v_idx:=v_min_ang;
  DBMS_OUTPUT.PUT_LINE('WHILE: ');
  WHILE (v_idx < v_max_ang) LOOP
      SELECT COUNT(ID_ANGAJAT) INTO v_verif FROM ANGAJATI WHERE ID_ANGAJAT=v_idx;
      if v_verif = 1 then
        SELECT ID_ANGAJAT, PRENUME, NUME, EMAIL, TELEFON, DATA_ANGAJARE, ID_FUNCTIE, SALARIUL, COMISION, ID_MANAGER, ID_DEPARTAMENT INTO v_id_angajat, v_prenume, v_nume, v_email, v_telefon, v_data_angajare, v_id_functie, v_salariul, v_comision, v_id_manager, v_id_departament FROM ANGAJATI WHERE ID_ANGAJAT=v_idx;
        DBMS_OUTPUT.PUT_LINE('ID ANGAJAT: ' || v_id_angajat || ', NUME: ' || v_nume || ', SALARIUL: ' || v_salariul);
      end if;
        v_idx:=v_idx+1;
  END LOOP;
  v_idx:=v_min_ang;
  DBMS_OUTPUT.PUT_LINE('DO WHILE: ');
  LOOP
    SELECT COUNT(ID_ANGAJAT) INTO v_verif FROM ANGAJATI WHERE ID_ANGAJAT=v_idx;
    if v_verif = 1 then
      SELECT ID_ANGAJAT, PRENUME, NUME, EMAIL, TELEFON, DATA_ANGAJARE, ID_FUNCTIE, SALARIUL, COMISION, ID_MANAGER, ID_DEPARTAMENT INTO v_id_angajat, v_prenume, v_nume, v_email, v_telefon, v_data_angajare, v_id_functie, v_salariul, v_comision, v_id_manager, v_id_departament FROM ANGAJATI WHERE ID_ANGAJAT=v_idx;
      DBMS_OUTPUT.PUT_LINE('ID ANGAJAT: ' || v_id_angajat || ', NUME: ' || v_nume || ', SALARIUL: ' || v_salariul);
    end if;
      v_idx:=v_idx+1;
  EXIT WHEN v_idx > v_max_ang;
  END LOOP;
END;
/

--4. Printr-o comandă SQL simplă, să se șteargă angajatul cu id_angajat 150

DELETE FROM ANGAJATI WHERE ID_ANGAJAT = 150;
ROLLBACK;

--5. Printr-o comandă SQL simplă, să se afișeze numele utilizatorului curent și data sistemului (utilizând USER și SYSDATE)
 
SELECT USER, SYSDATE FROM DUAL;

--6. Într-un bloc PL/SQL să se parcurgă toți angajații, folosind pe rând structurile: FOR-LOOP, WHILE-LOOP, LOOP-EXIT WHEN

DECLARE
  v_min_ang NUMBER;
  v_max_ang NUMBER;
  v_idx NUMBER;
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
  v_verif NUMBER;
BEGIN
  SELECT MIN(ID_ANGAJAT), MAX(ID_ANGAJAT) INTO v_min_ang, v_max_ang FROM ANGAJATI;
  DBMS_OUTPUT.PUT_LINE('FOR: ');
  FOR IDX IN v_min_ang..v_max_ang LOOP
    SELECT COUNT(ID_ANGAJAT) INTO v_verif FROM ANGAJATI WHERE ID_ANGAJAT=IDX;
    if v_verif = 1 then
      SELECT ID_ANGAJAT, PRENUME, NUME, EMAIL, TELEFON, DATA_ANGAJARE, ID_FUNCTIE, SALARIUL, COMISION, ID_MANAGER, ID_DEPARTAMENT INTO v_id_angajat, v_prenume, v_nume, v_email, v_telefon, v_data_angajare, v_id_functie, v_salariul, v_comision, v_id_manager, v_id_departament FROM ANGAJATI WHERE ID_ANGAJAT=IDX;
      DBMS_OUTPUT.PUT_LINE('ID ANGAJAT: ' || v_id_angajat || ', NUME: ' || v_nume || ', SALARIUL: ' || v_salariul);
    end if;
  END LOOP;
  v_idx:=v_min_ang;
  DBMS_OUTPUT.PUT_LINE('WHILE: ');
  WHILE (v_idx < v_max_ang) LOOP
      SELECT COUNT(ID_ANGAJAT) INTO v_verif FROM ANGAJATI WHERE ID_ANGAJAT=v_idx;
      if v_verif = 1 then
        SELECT ID_ANGAJAT, PRENUME, NUME, EMAIL, TELEFON, DATA_ANGAJARE, ID_FUNCTIE, SALARIUL, COMISION, ID_MANAGER, ID_DEPARTAMENT INTO v_id_angajat, v_prenume, v_nume, v_email, v_telefon, v_data_angajare, v_id_functie, v_salariul, v_comision, v_id_manager, v_id_departament FROM ANGAJATI WHERE ID_ANGAJAT=v_idx;
        DBMS_OUTPUT.PUT_LINE('ID ANGAJAT: ' || v_id_angajat || ', NUME: ' || v_nume || ', SALARIUL: ' || v_salariul);
      end if;
        v_idx:=v_idx+1;
  END LOOP;
  v_idx:=v_min_ang;
  DBMS_OUTPUT.PUT_LINE('DO WHILE: ');
  LOOP
    SELECT COUNT(ID_ANGAJAT) INTO v_verif FROM ANGAJATI WHERE ID_ANGAJAT=v_idx;
    if v_verif = 1 then
      SELECT ID_ANGAJAT, PRENUME, NUME, EMAIL, TELEFON, DATA_ANGAJARE, ID_FUNCTIE, SALARIUL, COMISION, ID_MANAGER, ID_DEPARTAMENT INTO v_id_angajat, v_prenume, v_nume, v_email, v_telefon, v_data_angajare, v_id_functie, v_salariul, v_comision, v_id_manager, v_id_departament FROM ANGAJATI WHERE ID_ANGAJAT=v_idx;
      DBMS_OUTPUT.PUT_LINE('ID ANGAJAT: ' || v_id_angajat || ', NUME: ' || v_nume || ', SALARIUL: ' || v_salariul);
    end if;
      v_idx:=v_idx+1;
  EXIT WHEN v_idx > v_max_ang;
  END LOOP;
END;
/