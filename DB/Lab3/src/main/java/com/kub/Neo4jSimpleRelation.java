package com.kub;

import java.util.Optional;

public class Neo4jSimpleRelation {
    Neo4jSimpleNode from;
    Neo4jSimpleNode to;
    Relation relation;

    Neo4jSimpleRelation(Neo4jSimpleNode from, Neo4jSimpleNode to, Relation relation) {
        this.from = from;
        this.to = to;
        this.relation = relation;
    }

    public String constructQuery() {
        String query = "MATCH (f:" + from.getLabel() +"{name:\"" + from.getName() + "\"}), ";
        query += "(t:" + to.getLabel() + "{name:\"" + to.getName() + "\"}) ";
        query += "create (f)-[r:" + relation.getRelation()+"]->(t)";
        return query;
    }

}
