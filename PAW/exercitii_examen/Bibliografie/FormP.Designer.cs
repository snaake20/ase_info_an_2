namespace Bibliografie
{
	partial class FormP
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.menuStrip1 = new System.Windows.Forms.MenuStrip();
			this.dateToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.adaugaManualToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.LVPublicatii = new System.Windows.Forms.ListView();
			this.titlu = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.isbn = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.categorie = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.pret = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.LVAutori = new System.Windows.Forms.ListView();
			this.nume = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.gradDidactic = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.marca = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.menuStrip1.SuspendLayout();
			this.SuspendLayout();
			// 
			// menuStrip1
			// 
			this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.dateToolStripMenuItem});
			this.menuStrip1.Location = new System.Drawing.Point(0, 0);
			this.menuStrip1.Name = "menuStrip1";
			this.menuStrip1.Size = new System.Drawing.Size(800, 24);
			this.menuStrip1.TabIndex = 0;
			this.menuStrip1.Text = "menuStrip1";
			// 
			// dateToolStripMenuItem
			// 
			this.dateToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.adaugaManualToolStripMenuItem});
			this.dateToolStripMenuItem.Name = "dateToolStripMenuItem";
			this.dateToolStripMenuItem.Size = new System.Drawing.Size(43, 20);
			this.dateToolStripMenuItem.Text = "Date";
			// 
			// adaugaManualToolStripMenuItem
			// 
			this.adaugaManualToolStripMenuItem.Name = "adaugaManualToolStripMenuItem";
			this.adaugaManualToolStripMenuItem.Size = new System.Drawing.Size(158, 22);
			this.adaugaManualToolStripMenuItem.Text = "Adauga manual";
			this.adaugaManualToolStripMenuItem.Click += new System.EventHandler(this.adaugaManualToolStripMenuItem_Click);
			// 
			// LVPublicatii
			// 
			this.LVPublicatii.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.titlu,
            this.isbn,
            this.categorie,
            this.pret});
			this.LVPublicatii.FullRowSelect = true;
			this.LVPublicatii.GridLines = true;
			this.LVPublicatii.HideSelection = false;
			this.LVPublicatii.Location = new System.Drawing.Point(12, 27);
			this.LVPublicatii.Name = "LVPublicatii";
			this.LVPublicatii.Size = new System.Drawing.Size(340, 229);
			this.LVPublicatii.TabIndex = 1;
			this.LVPublicatii.UseCompatibleStateImageBehavior = false;
			this.LVPublicatii.View = System.Windows.Forms.View.Details;
			this.LVPublicatii.SelectedIndexChanged += new System.EventHandler(this.LVPublicatii_SelectedIndexChanged);
			// 
			// titlu
			// 
			this.titlu.Text = "Titlu";
			// 
			// isbn
			// 
			this.isbn.Text = "ISBN";
			// 
			// categorie
			// 
			this.categorie.Text = "Categorie";
			// 
			// pret
			// 
			this.pret.Text = "Pret";
			// 
			// LVAutori
			// 
			this.LVAutori.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.nume,
            this.gradDidactic,
            this.marca});
			this.LVAutori.FullRowSelect = true;
			this.LVAutori.GridLines = true;
			this.LVAutori.HideSelection = false;
			this.LVAutori.Location = new System.Drawing.Point(479, 27);
			this.LVAutori.Name = "LVAutori";
			this.LVAutori.Size = new System.Drawing.Size(309, 229);
			this.LVAutori.TabIndex = 2;
			this.LVAutori.UseCompatibleStateImageBehavior = false;
			this.LVAutori.View = System.Windows.Forms.View.Details;
			this.LVAutori.ItemDrag += new System.Windows.Forms.ItemDragEventHandler(this.LVAutori_ItemDrag);
			// 
			// nume
			// 
			this.nume.Text = "Nume";
			// 
			// gradDidactic
			// 
			this.gradDidactic.Text = "Grad Didactic";
			this.gradDidactic.Width = 85;
			// 
			// marca
			// 
			this.marca.Text = "Marca";
			// 
			// textBox1
			// 
			this.textBox1.AllowDrop = true;
			this.textBox1.Location = new System.Drawing.Point(12, 262);
			this.textBox1.Multiline = true;
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new System.Drawing.Size(340, 176);
			this.textBox1.TabIndex = 3;
			this.textBox1.DragDrop += new System.Windows.Forms.DragEventHandler(this.textBox1_DragDrop);
			this.textBox1.DragEnter += new System.Windows.Forms.DragEventHandler(this.textBox1_DragEnter);
			// 
			// FormP
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(800, 450);
			this.Controls.Add(this.textBox1);
			this.Controls.Add(this.LVAutori);
			this.Controls.Add(this.LVPublicatii);
			this.Controls.Add(this.menuStrip1);
			this.MainMenuStrip = this.menuStrip1;
			this.Name = "FormP";
			this.Text = "Formular Principal";
			this.Load += new System.EventHandler(this.FormP_Load);
			this.menuStrip1.ResumeLayout(false);
			this.menuStrip1.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.MenuStrip menuStrip1;
		private System.Windows.Forms.ToolStripMenuItem dateToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem adaugaManualToolStripMenuItem;
		private System.Windows.Forms.ListView LVPublicatii;
		private System.Windows.Forms.ColumnHeader titlu;
		private System.Windows.Forms.ColumnHeader isbn;
		private System.Windows.Forms.ColumnHeader categorie;
		private System.Windows.Forms.ColumnHeader pret;
		private System.Windows.Forms.ListView LVAutori;
		private System.Windows.Forms.ColumnHeader nume;
		private System.Windows.Forms.ColumnHeader gradDidactic;
		private System.Windows.Forms.ColumnHeader marca;
		private System.Windows.Forms.TextBox textBox1;
	}
}

