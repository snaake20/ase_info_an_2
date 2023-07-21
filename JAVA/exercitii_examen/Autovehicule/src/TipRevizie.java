public enum TipRevizie {
    ITP("ITP"),
    TPU("TPU");

    private String tip;

    TipRevizie(String tip) {
        this.tip = tip;
    }

    public String getTip() {
        return tip;
    }
}
