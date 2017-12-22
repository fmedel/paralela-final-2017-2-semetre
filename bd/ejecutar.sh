##Build an image from the Dockerfile assign it a name.
docker build -t ubuntu_prueba_bd .
##Run the PostgreSQL server container (in the foreground):
docker run  --rm -p 8082:5432 --name pg_test ubuntu_prueba_bd

##de donde lo saque 
## https://docs.docker.com/engine/examples/postgresql_service/


