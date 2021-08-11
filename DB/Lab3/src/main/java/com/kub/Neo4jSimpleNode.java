package com.kub;

enum Label{
    ACTOR("Actor"), FILM("Film");

    private String label;

    Label(String label) {
        this.label = label;
    }

    public String getLabel() {
        return label;
    }
}

enum Relation{
    PLAYS_IN("plays_in"),LIKES("likes");
    private String relation;

    Relation(String rel){
        relation = rel;
    }

    public String getRelation() {
        return relation;
    }
}

public class Neo4jSimpleNode {
    private String name;
    private Label label;

    public Neo4jSimpleNode(String name, Label label) {
        this.name = name;
        this.label = label;
    }

    public String getName() {
        return name;
    }

    public String getLabel() {
        return label.getLabel();
    }
}
