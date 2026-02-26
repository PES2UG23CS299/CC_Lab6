pipeline {
    agent any
    stages {
        stage('Build Backend Image') {
            steps {
                sh 'docker build -t backend-app backend'
            }
        }
        stage('Deploy Backends') {
            steps {
                sh 'docker rm -f backend1 backend2 || true'
                sh 'docker run -d --name backend1 backend-app'
                sh 'docker run -d --name backend2 backend-app'
            }
        }
        stage('Deploy NGINX Load Balancer') {
    steps {
        sh 'docker rm -f nginx-lb || true'
        // Run NGINX on the network
        sh 'docker run -d --name nginx-lb --network lab6-net -p 80:80 nginx'
        
        // Give the network and backends more time to register in Docker DNS
        sleep 5 
        
        // Copy the config
        sh 'docker cp nginx/default.conf nginx-lb:/etc/nginx/conf.d/default.conf'
        
        // Final reload
        sh 'docker exec nginx-lb nginx -s reload'}
        }
    }
}
