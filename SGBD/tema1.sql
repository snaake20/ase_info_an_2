-- 1. Construiți un bloc PL/SQL prin care să se calculeze într-o variabilă globală venitul total al unui angajat pentru care identificatorul este citit de la tastatură.
VAR g_venit_total NUMBER;
DECLARE
  v_id ANGAJATI.ID_ANGAJAT%TYPE := &ID_ANGAJAT;
BEGIN
  select SALARIUL + (SALARIUL * NVL(COMISION, 0)) INTO :g_venit_total FROM ANGAJATI WHERE ID_ANGAJAT = v_id;
END;
/
-- 2. Construiți un bloc PL/SQL prin care să se calculeze într-o variabilă globală salariul mediu al angajaților din departamentul al cărui identificator este citit de la tastatură.
VAR g_sal_mediu NUMBER;
DECLARE
  v_id_departament ANGAJATI.ID_DEPARTAMENT%TYPE := &ID_DEPARTAMENT;
BEGIN
  select AVG(SALARIUL) INTO :g_sal_mediu FROM ANGAJATI WHERE ID_DEPARTAMENT = v_id_departament;
END;
/
-- 3. Printr-o comandă SQL, să se afișeze informații despre angajații cu salariul mai mare decât salariul mediu calculat la exercițiul 2.
SELECT ID_ANGAJAT, NUME || ' ' || PRENUME, SALARIUL FROM ANGAJATI WHERE SALARIUL > :g_sal_mediu;
-- 4. Construiți un bloc PL/SQL prin care să se calculeze (în variabile locale) și să se afișeze contribuțiile și salariul net pentru angajatul 100. (procentele necesar de aplicat sunt: CAS - 25%, CASS - 10%, Impozit - 10%). 
DECLARE
  v_cas NUMBER;
  v_cass NUMBER;
  v_impozit NUMBER;
  v_salariu_net NUMBER;
BEGIN
  SELECT SALARIUL * 0.25, SALARIUL * 0.1, (SALARIUL - (SALARIUL * 0.35)) * 0.1, SALARIUL - (SALARIUL * 0.35) - ((SALARIUL - (SALARIUL * 0.35)) * 0.1) INTO v_cas, v_cass, v_impozit, v_salariu_net FROM SALARIATI WHERE ID_ANGAJAT = 100;
  DBMS_OUTPUT.PUT_LINE('CAS:' || v_cas || ' CASS: ' || v_cass || ' IMPOZIT: ' || v_impozit || ' SALARIU NET: ' || v_salariu_net);
END;
/
-- 5. Construiți un bloc PL/SQL prin care să se adauge un produs nou în tabela Produse, astfel:

-- valoarea coloanei id_produs va fi calculată ca fiind maximul valorilor existente, incrementat cu 1
-- valorile coloanelor denumire_produs și descriere vor fi citite de la tastatură prin variabile de substituție
-- restul valorilor pot rămâne NULL
DECLARE
  v_id_produs PRODUSE.ID_PRODUS%TYPE;
  v_denumire PRODUSE.DENUMIRE_PRODUS%TYPE := '&denumire';
  v_descriere PRODUSE.DENUMIRE_PRODUS%TYPE := '&descriere';
BEGIN
  SELECT MAX(ID_PRODUS) into v_id_produs FROM PRODUSE;
  INSERT INTO PRODUSE (ID_PRODUS, DENUMIRE_PRODUS, DESCRIERE) VALUES (v_id_produs + 1, v_denumire, v_descriere);
END;
/

--SELECT * FROM PRODUSE WHERE ID_PRODUS = (SELECT MAX(ID_PRODUS) FROM PRODUSE); --test