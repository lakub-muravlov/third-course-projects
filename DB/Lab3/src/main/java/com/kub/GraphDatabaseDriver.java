package com.kub;
import org.neo4j.driver.*;

public class GraphDatabaseDriver {
    private Driver driver;
    private String uri;
    private String username;
    private String password;

    GraphDatabaseDriver() {

    }

    GraphDatabaseDriver(String uri, String username, String password) {
        this.uri = uri;
        this.username = username;
        this.password = password;
    }

    public static GraphDatabaseDriver getAndInitDriver(String uri, String username, String password){
        GraphDatabaseDriver driver = new GraphDatabaseDriver(uri,username, password);
        driver.initDriver();
        return driver;
    }

    public void initDriver(){
        driver = GraphDatabase.driver(uri, AuthTokens.basic(username,password));
    }

    public void closeDriver(){
        driver.close();
    }

    public Session getSession() {
        return driver.session();
    }
}
