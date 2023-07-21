namespace Pizzeria
{
	partial class AfisareComenzi
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
			this.TVComenzi = new System.Windows.Forms.TreeView();
			this.SuspendLayout();
			// 
			// TVComenzi
			// 
			this.TVComenzi.Location = new System.Drawing.Point(13, 13);
			this.TVComenzi.Name = "TVComenzi";
			this.TVComenzi.Size = new System.Drawing.Size(450, 327);
			this.TVComenzi.TabIndex = 0;
			// 
			// AfisareComenzi
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(800, 450);
			this.Controls.Add(this.TVComenzi);
			this.Name = "AfisareComenzi";
			this.Text = "AfisareComenzi";
			this.Load += new System.EventHandler(this.AfisareComenzi_Load);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.TreeView TVComenzi;
	}
}