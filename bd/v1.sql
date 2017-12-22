--
-- PostgreSQL database dump
--

-- Dumped from database version 9.5.10
-- Dumped by pg_dump version 9.5.10

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner:
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner:
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: camino; Type: TABLE; Schema: public; Owner: docker
--

CREATE TABLE camino (
    id_camino bigint NOT NULL,
    inicio_fila integer NOT NULL,
    fin_fila integer NOT NULL,
    inicio_columna integer NOT NULL,
    fin_columna integer NOT NULL,
    solucion integer DEFAULT 0,
    camino text,
    seccion_fila integer,
    seccion_columna integer,
    columna_fila integer
);


ALTER TABLE camino OWNER TO docker;

--
-- Name: camino_id_camino_seq; Type: SEQUENCE; Schema: public; Owner: docker
--

CREATE SEQUENCE camino_id_camino_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE camino_id_camino_seq OWNER TO docker;

--
-- Name: camino_id_camino_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: docker
--

ALTER SEQUENCE camino_id_camino_seq OWNED BY camino.id_camino;


--
-- Name: laberinto; Type: TABLE; Schema: public; Owner: docker
--

CREATE TABLE laberinto (
    id_laberinto bigint NOT NULL,
    fila integer NOT NULL,
    columna integer NOT NULL,
    valor boolean DEFAULT false,
    seccion_fila integer NOT NULL,
    seccion_columna integer NOT NULL
);


ALTER TABLE laberinto OWNER TO docker;

--
-- Name: laberinto_id_laberinto_seq; Type: SEQUENCE; Schema: public; Owner: docker
--

CREATE SEQUENCE laberinto_id_laberinto_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE laberinto_id_laberinto_seq OWNER TO docker;

--
-- Name: laberinto_id_laberinto_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: docker
--

ALTER SEQUENCE laberinto_id_laberinto_seq OWNED BY laberinto.id_laberinto;


--
-- Name: id_camino; Type: DEFAULT; Schema: public; Owner: docker
--

ALTER TABLE ONLY camino ALTER COLUMN id_camino SET DEFAULT nextval('camino_id_camino_seq'::regclass);


--
-- Name: id_laberinto; Type: DEFAULT; Schema: public; Owner: docker
--

ALTER TABLE ONLY laberinto ALTER COLUMN id_laberinto SET DEFAULT nextval('laberinto_id_laberinto_seq'::regclass);


--
-- Data for Name: camino; Type: TABLE DATA; Schema: public; Owner: docker
--


--
-- Name: camino_pkey; Type: CONSTRAINT; Schema: public; Owner: docker
--

ALTER TABLE ONLY camino
    ADD CONSTRAINT camino_pkey PRIMARY KEY (id_camino);


--
-- Name: laberinto_pkey; Type: CONSTRAINT; Schema: public; Owner: docker
--

ALTER TABLE ONLY laberinto
    ADD CONSTRAINT laberinto_pkey PRIMARY KEY (id_laberinto);


--
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- PostgreSQL database dump complete
