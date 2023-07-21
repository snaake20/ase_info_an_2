DECLARE
  v_nr NUMBER;
  v_id clienti.id_client%TYPE := &id;
  v_nume CLIENTI.NUME_CLIENT%TYPE;
  v_id_comanda COMENZI.ID_COMANDA%TYPE;
  v_data COMENZI.DATA%TYPE;
  v_valoare NUMBER;
  v_nr_comenzi NUMBER;
  nu_exista_client EXCEPTION;
BEGIN
  SELECT COUNT(ID_CLIENT) INTO v_nr FROM CLIENTI WHERE ID_CLIENT = v_id;
  IF v_nr = 0 THEN
    RAISE nu_exista_client;
  ELSE
    SELECT NUME_CLIENT into v_nume FROM CLIENTI WHERE ID_CLIENT = v_id;
    DBMS_OUTPUT.PUT_LINE('Numele clientului: ' || v_nume);
    SELECT COM.ID_COMANDA, COM.DATA, SUM(RC.PRET*RC.CANTITATE) INTO v_id_comanda, v_data, v_valoare FROM COMENZI COM, RAND_COMENZI RC WHERE COM.ID_CLIENT = v_id AND COM.ID_COMANDA = RC.ID_COMANDA GROUP BY COM.ID_COMANDA, COM.DATA;
    DBMS_OUTPUT.PUT_LINE(v_id_comanda || ' ' || v_data || ' ' || v_valoare);
  END IF;
EXCEPTION
  WHEN nu_exista_client THEN
    DBMS_OUTPUT.PUT_LINE('Clientul cu id-ul: ' || v_id || ' nu exista!');
  WHEN NO_DATA_FOUND THEN
    DBMS_OUTPUT.PUT_LINE('Clientul cu id-ul: ' || v_id || ' exista, dar nu are comenzi');
  WHEN TOO_MANY_ROWS THEN
    DBMS_OUTPUT.PUT_LINE('Prea multe comenzi');
    DECLARE
      CURSOR C IS SELECT COM.ID_COMANDA ID, COM.DATA D_FIN, SUM(RC.PRET*RC.CANTITATE) VAL  FROM COMENZI COM, RAND_COMENZI RC WHERE COM.ID_CLIENT = v_id AND COM.ID_COMANDA = RC.ID_COMANDA GROUP BY COM.ID_COMANDA, COM.DATA;
    BEGIN
      OPEN C;
      LOOP
        EXIT WHEN C%NOTFOUND;
        FETCH C INTO v_id_comanda, v_data, v_valoare;
        DBMS_OUTPUT.PUT_LINE(v_id_comanda || ' ' || v_data || ' ' || v_valoare);
      END LOOP;
      CLOSE C;
      -- for v in c loop
        -- DBMS_OUTPUT.PUT_LINE(v.id || ' ' || v.d_fin || ' ' || v.val);
      -- end loop;
    END;
    SELECT COUNT(ID_COMANDA) INTO v_nr_comenzi FROM COMENZI WHERE ID_CLIENT = v_id;
    DBMS_OUTPUT.PUT_LINE('Nr comenzi: ' || v_nr_comenzi);
END;
/